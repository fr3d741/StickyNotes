#include <stickywidget.h>

#include <QApplication>
#include <Controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller::loadNotes();
    return a.exec();
}
