#ifndef STICKYWIDGET_H
#define STICKYWIDGET_H

#include <QWidget>
#include <QPoint>
#include <memory>

class INoteRepository;
class QMenu;

QT_BEGIN_NAMESPACE
namespace Ui { class StickyWidget; }
QT_END_NAMESPACE

class StickyWidget : public QWidget
{
    Q_OBJECT

public:
    StickyWidget(QWidget *parent, INoteRepository* repository);
    StickyWidget(QWidget* parent, INoteRepository* repository, QString id);
    ~StickyWidget();

    virtual bool eventFilter(QObject* watched, QEvent* event) override;

    const QString id() const;

protected:
    virtual void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_textEdit_textChanged();

private:
    void init();
    void updateTitle();
    void showContextMenu(QContextMenuEvent* event, QMenu* m = nullptr);

private:
    INoteRepository* repository_;
    bool block_reentrancy_;
    QPoint last_pos_;
    QString title_;
    QString id_;
    std::unique_ptr<Ui::StickyWidget> ui;
};
#endif // STICKYWIDGET_H
