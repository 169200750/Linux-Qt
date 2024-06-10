#ifndef FIRST_H
#define FIRST_H

#include <QWidget>
#include "widget.h"
#include <QString>
namespace Ui {
class First;
}

class First : public QWidget
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = nullptr);
    ~First();

private slots:
    void on_pushButton_clicked();

private:
    Ui::First *ui;
    Widget *my_next;
};

#endif // FIRST_H
