#include "stickywidget.h"

#include <QApplication>
#include <stickyfactory.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = StickyFactory::createWidget();
    w->show();
    return a.exec();
}
