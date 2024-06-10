#include "first.h"
#include "ui_first.h"
#include <QString>
#include "QMessageBox"
First::First(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("登录界面"));
}

First::~First()
{
    delete ui;
}

void First::on_pushButton_clicked()
{
    if(ui->username->text()=="admin" && ui->password->text()=="123")
     {
     my_next=new Widget;
     connect(my_next,SIGNAL(back()),this,SLOT(show()));
     this->hide();
     my_next->show();}
    else {
        QMessageBox::question(this,tr("警告"),tr("用户名或密码错误"),QMessageBox::Yes);
    }
}
