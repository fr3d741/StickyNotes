#include <stickyfactory.h>
#include <stickywidget.h>
#include <stickycontainer.h>

StickyWidget* StickyFactory::createWidget()
{
    auto w = new StickyWidget(StickyContainer::Instance().mainWidget());
    StickyContainer::Instance().addWidget(w);
    return w;
}

void StickyFactory::removeWidget(StickyWidget* w){

    StickyContainer::Instance().removeWidget(w);
}
