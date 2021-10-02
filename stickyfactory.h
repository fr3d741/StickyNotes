#ifndef STICKYFACTORY_H
#define STICKYFACTORY_H

class StickyWidget;

class StickyFactory
{
    StickyFactory() = delete;
public:
    static StickyWidget* createWidget();
    static void removeWidget(StickyWidget* w);
};

#endif // STICKYFACTORY_H
