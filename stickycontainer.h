#ifndef STICKYCONTAINER_H
#define STICKYCONTAINER_H

#include <QList>
#include <QMap>

class StickyWidget;
class QWidget;

class StickyContainer
{
    StickyWidget* main_widget_ = nullptr;
    QList<StickyWidget*> widgets_;
private:
    StickyContainer();
    StickyContainer(StickyContainer&) = delete;
    StickyContainer(StickyContainer&&) = delete;

    void removeWidget(StickyWidget* widget);
    void addWidget(StickyWidget* widget);
public:
    static StickyContainer& instance();
    static StickyWidget* createWidget();
    static StickyWidget* createWidget(QString id);
    static void removeWidget(QWidget* w);
    static void removeWidget(QString id);

    StickyWidget* mainWidget();

    QMap<QString, QString> visibleWidgets();

    void saveState();
    void loadState();
};

#endif // STICKYCONTAINER_H
