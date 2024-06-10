/********************************************************************************
** Form generated from reading UI file 'first.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRST_H
#define UI_FIRST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_First
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *pushButton;

    void setupUi(QWidget *First)
    {
        if (First->objectName().isEmpty())
            First->setObjectName(QString::fromUtf8("First"));
        First->resize(400, 300);
        label = new QLabel(First);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 30, 171, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(First);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(51, 111, 60, 16));
        label_3 = new QLabel(First);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 150, 72, 15));
        username = new QLineEdit(First);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(120, 110, 171, 21));
        password = new QLineEdit(First);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(120, 150, 171, 21));
        password->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(First);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 210, 93, 28));

        retranslateUi(First);

        QMetaObject::connectSlotsByName(First);
    } // setupUi

    void retranslateUi(QWidget *First)
    {
        First->setWindowTitle(QCoreApplication::translate("First", "Form", nullptr));
        label->setText(QCoreApplication::translate("First", "\347\275\221\347\273\234\350\201\212\345\244\251\345\256\244", nullptr));
        label_2->setText(QCoreApplication::translate("First", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("First", "\345\257\206 \347\240\201\357\274\232", nullptr));
        password->setText(QString());
        pushButton->setText(QCoreApplication::translate("First", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class First: public Ui_First {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRST_H
