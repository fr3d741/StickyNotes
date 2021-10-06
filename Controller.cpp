#include <Controller.h>
#include <NoteRepository.h>
#include <stickycontainer.h>

#include <QApplication>
#include <QMenu>

Controller::Controller()
{
}

Controller::~Controller()
{
}

Controller& Controller::instance()
{
    static Controller instance;
    return instance;
}

void Controller::loadNotes() 
{
    NoteRepository::instance().loadNotes();
    auto&& instance = StickyContainer::instance();
    instance.loadState();

    if (instance.mainWidget() == nullptr)
        instance.createWidget();
}

void Controller::saveNotes()
{
    NoteRepository::instance().saveNotes();
    StickyContainer::instance().saveState();
}

void Controller::addWidget() {

    StickyContainer::createWidget();
}

void Controller::removeWidget(QWidget* widget) {

    StickyContainer::removeWidget(widget);
}

void Controller::addActions(QMenu* menu)
{
    auto visible = StickyContainer::instance().visibleWidgets();
    auto all_note = NoteRepository::instance().getNoteTitles();

    QMenu* sub_menu = new QMenu("Notes", menu);
    menu->addMenu(sub_menu);
    for (auto it = all_note.begin(); it != all_note.end(); ++it)
    {
        auto action = sub_menu->addAction(it.value());
        action->setCheckable(true);
        const bool is_checked = visible.contains(it.key());
        action->setChecked(is_checked);
        action->setData(QVariant(it.key()));
        connect(action, &QAction::triggered, this, &Controller::slotChangeNoteVisibility);
    }

    auto action = menu->addAction("Quit");
    connect(action, &QAction::triggered, this, &Controller::slotQuit);
}

void Controller::slotQuit() {

    NoteRepository::instance().saveNotes();
    StickyContainer::instance().saveState();
    QApplication::quit();
}

void Controller::slotChangeNoteVisibility(bool enabled)
{
    auto action = static_cast<QAction*>(sender());
    auto id = action->data().toString();
    if (enabled)
        StickyContainer::createWidget(id);
    else
        StickyContainer::removeWidget(id);
}
