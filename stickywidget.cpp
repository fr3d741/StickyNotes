#include <QTextBlock>
#include <QTextStream>
#include <QMenu>

#include "stickywidget.h"
#include <stickyfactory.h>
#include <stickycontainer.h>
#include "ui_stickywidget.h"

StickyWidget::StickyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StickyWidget)
{
    block_reentrancy_ = false;
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    //setWindowFlags(Qt::Dialog);
    //setWindowFlags(Qt::CustomizeWindowHint);
    setWindowModality(Qt::NonModal);
    //setContextMenuPolicy(Qt::CustomContextMenu);
}

StickyWidget::~StickyWidget()
{
}

bool StickyWidget::eventFilter(QObject* /*watched*/, QEvent* event) {

  if (event->type() != QEvent::ContextMenu)
    return false;

  return false;
}

void StickyWidget::contextMenuEvent(QContextMenuEvent* /*event*/) {

  std::unique_ptr<QMenu> menu = std::make_unique<QMenu>();
  auto action = menu->addAction("Quit");
  connect(action, &QAction::triggered, this, &StickyWidget::slotQuit);
  menu->exec();
}

void StickyWidget::on_addButton_clicked()
{
    auto w = StickyFactory::createWidget();
    w->show();
}


void StickyWidget::on_deleteButton_clicked()
{
    StickyFactory::removeWidget(this);
    close();
}

void StickyWidget::on_textEdit_textChanged()
{
    auto block = ui->textEdit->document()->firstBlock();
    auto content = block.text();
    QTextStream stream(&content);
    title_ = stream.readLine();
    setWindowTitle(title_);
    ui->title->setText(title_);
}

void StickyWidget::slotQuit() {

  StickyContainer::Instance().save();
}
