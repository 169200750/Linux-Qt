#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_send_clicked();
    void Mynetted();
    void on_pushButton_clicked();
    void ReadServer();
    void on_Exr_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    char buf[1024*1024]={0};
};
#endif // WIDGET_H
