#include <QTextBlock>
#include <QTextStream>
#include <QMenu>

#include <stickywidget.h>
#include <INoteRepository.h>
#include <Controller.h>

#include "ui_stickywidget.h"

StickyWidget::StickyWidget(QWidget *parent, INoteRepository* repository)
    : QWidget(parent)
    , repository_(repository)
    , ui(new Ui::StickyWidget)
{
    init();
    id_ = repository_->generateId();
}

StickyWidget::StickyWidget(QWidget *parent, INoteRepository* repository, QString id)
    : QWidget(parent)
    , repository_(repository)
    , id_(id)
    , ui(new Ui::StickyWidget)
{
    init();
    ui->textEdit->setText(repository_->load(id_));
}

StickyWidget::~StickyWidget()
{
}

bool StickyWidget::eventFilter(QObject* /*watched*/, QEvent* event) {

  if (event->type() != QEvent::ContextMenu)
    return false;

  showContextMenu(static_cast<QContextMenuEvent*>(event), ui->textEdit->createStandardContextMenu());
  return true;
}

const QString StickyWidget::id() const
{
    return id_;
}

void StickyWidget::contextMenuEvent(QContextMenuEvent* event) {

    showContextMenu(event);
}

void StickyWidget::on_addButton_clicked()
{
    Controller::instance().addWidget();
}

void StickyWidget::on_deleteButton_clicked()
{
    Controller::instance().removeWidget(this);
}

void StickyWidget::on_textEdit_textChanged()
{
    updateTitle();

    QString text = ui->textEdit->document()->toPlainText();
    repository_->store(id_, text);
}

void StickyWidget::init()
{
    block_reentrancy_ = false;
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setWindowModality(Qt::NonModal);
    ui->textEdit->viewport()->installEventFilter(this);

    //const QString styles_sheet =
    //    "* { background-color: rgb(255,0,0) }";

    //qApp->setStyleSheet(styles_sheet);
}

void StickyWidget::updateTitle()
{

    auto block = ui->textEdit->document()->firstBlock();
    auto content = block.text();
    QTextStream stream(&content);
    title_ = stream.readLine();
    setWindowTitle(title_);
    ui->title->setText(title_);
}

void StickyWidget::showContextMenu(QContextMenuEvent* event, QMenu* m) {

    auto menu = new QMenu(this);
    if (m != nullptr) {
        m->setTitle("Actions");
        menu->addMenu(m);
        menu->addSeparator();
    }
    Controller::instance().addActions(menu);
    menu->exec(event->globalPos());
}

