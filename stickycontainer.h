#ifndef STICKYCONTAINER_H
#define STICKYCONTAINER_H

#include <QList>

class StickyWidget;

class StickyContainer
{
    StickyWidget* main_widget_;
    QList<StickyWidget*> widgets_;
private:
    StickyContainer();
    StickyContainer(StickyContainer&) = delete;
    StickyContainer(StickyContainer&&) = delete;
public:
    static StickyContainer& Instance();

    void addWidget(StickyWidget* widget);
    void removeWidget(StickyWidget* widget);
    StickyWidget* mainWidget();
    void save();
};

#endif // STICKYCONTAINER_H
