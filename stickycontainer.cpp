#include "stickycontainer.h"
#include <stickywidget.h>

StickyContainer::StickyContainer()
{

}

StickyContainer& StickyContainer::Instance(){
    static StickyContainer instance_;
    return instance_;
}

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

    widgets_.removeOne(widget);
}

StickyWidget* StickyContainer::mainWidget(){
    return main_widget_;
}

void StickyContainer::save() {

  //for (auto w : widgets_) {

  //  QString path = QString("data\%1").arg(w->windowTitle());
  //  QTextStream output("data\texts.txt");
  //}
}
