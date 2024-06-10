/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *send_box;
    QTextEdit *Msg_show;
    QLineEdit *name;
    QPushButton *Exr;
    QPushButton *send;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(396, 369);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(221, 255, 243);"));
        send_box = new QTextEdit(Widget);
        send_box->setObjectName(QString::fromUtf8("send_box"));
        send_box->setGeometry(QRect(40, 236, 311, 41));
        send_box->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Msg_show = new QTextEdit(Widget);
        Msg_show->setObjectName(QString::fromUtf8("Msg_show"));
        Msg_show->setGeometry(QRect(41, 31, 311, 192));
        Msg_show->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        name = new QLineEdit(Widget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(40, 290, 91, 31));
        name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Exr = new QPushButton(Widget);
        Exr->setObjectName(QString::fromUtf8("Exr"));
        Exr->setGeometry(QRect(260, 290, 93, 31));
        Exr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        send = new QPushButton(Widget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(150, 290, 93, 31));
        send->setMaximumSize(QSize(16777215, 16777215));
        send->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        Exr->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        send->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
