#include <stickycontainer.h>
#include <stickywidget.h>
#include <NoteRepository.h>

#include <QDataStream>
#include <QFile>
#include <QDir>

static const char* SUBDIRECTORY = "windowstates";

/// Constructors

StickyContainer::StickyContainer()
{

}

/// STATIC FUNCTIONS 

StickyContainer& StickyContainer::instance(){
    static StickyContainer instance_;
    return instance_;
}

void StickyContainer::removeWidget(QString id)
{
    for (auto w : instance().widgets_)
    {
        if (w->id() != id)
            continue;

        instance().removeWidget(w);
        w->close();
        break;
    }
}

void StickyContainer::removeWidget(QWidget* w) {

    instance().removeWidget(static_cast<StickyWidget*>(w));
    w->close();
}

StickyWidget* StickyContainer::createWidget()
{
    auto w = new StickyWidget(instance().mainWidget(), &NoteRepository::instance());
    instance().addWidget(w);
    w->show();
    return w;
}

StickyWidget* StickyContainer::createWidget(QString id)
{
    auto w = new StickyWidget(instance().mainWidget(), &NoteRepository::instance(), id);
    instance().addWidget(w);
    w->show();
    return w;
}

/// PRIVATE FUNCTIONS 
void StickyContainer::addWidget(StickyWidget* widget){

    if (main_widget_ == nullptr)
        main_widget_ = widget;

    widgets_.push_back(widget);
}

void StickyContainer::removeWidget(StickyWidget* widget){

    if (main_widget_ == widget){

        StickyWidget* next_main_widget = nullptr;
        widgets_.takeFirst();
        for(auto child : widgets_){

            if (next_main_widget == nullptr)
            {
                next_main_widget = child;
                next_main_widget->setParent(nullptr);
                next_main_widget->show();
                continue;
            }

            child->setParent(next_main_widget, child->windowFlags());
            child->show();
        }

        main_widget_ = next_main_widget;
    }

    auto id = widget->id();
    QDir dir(SUBDIRECTORY, "");
    dir.remove(id);
    widgets_.removeOne(widget);
}

/// LOCAL FUNCTIONS 

StickyWidget* StickyContainer::mainWidget(){
    return main_widget_;
}

QMap<QString, QString> StickyContainer::visibleWidgets()
{
    QMap<QString, QString> map;
    for (auto w : widgets_) {
        map[w->id()] = w->windowTitle();
    }

    return map;
}

static void makeSureDirExists() {

    QFileInfo info(SUBDIRECTORY);
    if (!info.exists())
    {
        QDir dir;
        dir.mkdir(SUBDIRECTORY);
    }
}

void StickyContainer::saveState() {

    makeSureDirExists();

    for (auto w : widgets_) {
        const QString filename = QString("%1/%2").arg(SUBDIRECTORY).arg(w->id());
        QFile file(filename);
        file.open(QIODeviceBase::WriteOnly);
        if (!file.isOpen()) {
            qDebug() << "Saving states file not open";
            return;
        }

        QDataStream stream(&file);
        stream << w->saveGeometry();
        file.close();
    }
}

void StickyContainer::loadState() {

    QDir dir(SUBDIRECTORY, "");
    for (auto it : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {

        if (!it.isFile())
            continue;

        QFile file(it.filePath());
        file.open(QIODeviceBase::ReadOnly);
        if (!file.isOpen()) {
            qDebug() << "Loading states file not open";
            return;
        }

        QByteArray content;
        QDataStream input(&file);
        input >> content;

        auto w = new StickyWidget(main_widget_, &NoteRepository::instance(), it.fileName());
        addWidget(w);
        w->restoreGeometry(content);
        w->show();
    }
}
