/********************************************************************************
** Form generated from reading UI file 'stickywidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STICKYWIDGET_H
#define UI_STICKYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StickyWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *deleteButton;
    QPushButton *addButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textEdit;
    QLabel *title;

    void setupUi(QWidget *StickyWidget)
    {
        if (StickyWidget->objectName().isEmpty())
            StickyWidget->setObjectName(QString::fromUtf8("StickyWidget"));
        StickyWidget->resize(800, 600);
        gridLayout = new QGridLayout(StickyWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        deleteButton = new QPushButton(StickyWidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        gridLayout->addWidget(deleteButton, 0, 4, 1, 1);

        addButton = new QPushButton(StickyWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(305, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        textEdit = new QTextEdit(StickyWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 5);

        title = new QLabel(StickyWidget);
        title->setObjectName(QString::fromUtf8("title"));

        gridLayout->addWidget(title, 0, 2, 1, 1);


        retranslateUi(StickyWidget);

        QMetaObject::connectSlotsByName(StickyWidget);
    } // setupUi

    void retranslateUi(QWidget *StickyWidget)
    {
        StickyWidget->setWindowTitle(QCoreApplication::translate("StickyWidget", "StickyWidget", nullptr));
        deleteButton->setText(QCoreApplication::translate("StickyWidget", "X", nullptr));
        addButton->setText(QCoreApplication::translate("StickyWidget", "+", nullptr));
        title->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StickyWidget: public Ui_StickyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STICKYWIDGET_H
