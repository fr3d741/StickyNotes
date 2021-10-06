#pragma once

#include <QObject>

class QWidget;
class QMenu;

class Controller : public QObject {

    Q_OBJECT
    Controller();

public:
    ~Controller();

    static Controller& instance();
    static void loadNotes();

    static void saveNotes();
    static void addWidget();
    static void removeWidget(QWidget* widget);
    void addActions(QMenu* menu);

public slots:
    void slotQuit();
    void slotChangeNoteVisibility(bool enabled);
};
