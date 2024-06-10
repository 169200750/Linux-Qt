#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
//#include "QDate"
//#include "QTime"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
       this->setWindowTitle(tr("网络聊天室%1").arg(tr("--5组--")));
    socket = new QTcpSocket;
    connect(socket, SIGNAL(connected()), this, SLOT(Mynetted()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadServer()));
}

Widget::~Widget()
{
    delete ui;
}

//send函数
void Widget::on_send_clicked()
{

    QString data = ui->send_box->toPlainText();
    qDebug() << data;
    std::string str = data.toStdString();
    char buf[64] = {0};
    strcpy(buf, str.c_str());
    qDebug() << buf;
    socket->write(buf, 64);
}

//系统连接消息
void Widget::Mynetted()
{
    ui->Msg_show->append("连接聊天服务器成功");
}

//读取服务器发送来的数据
void Widget::ReadServer()
{
    QByteArray dataread = socket->readAll();
    QString s =QString::fromStdString(dataread.toStdString());
    qDebug()<< s;

//    QString str1 = QString::fromLocal8Bit(dataread);
    ui->Msg_show->append(s);
}

//服务器连接
void Widget::on_Exr_clicked()
{
    if(ui->Exr->text() == "连接服务器")
    {
        //连接到服务器
        socket->connectToHost("192.168.195.128", 8888);

        //将输入的用户名发送给服务器
        //读取文本框中的内容
        QString qname = ui->name->text();
        //类型转换
        std::string str = qname.toStdString();
        char buf[64] = {0};
        strcpy(buf, str.c_str());
        qDebug() << buf;
        socket->write(buf,64);
        QString show_txt = "断开服务器" ;
        ui->Exr->setText(show_txt);
    }
    else
    {
        socket->close();
        //退出
        this->close();
    }
}
