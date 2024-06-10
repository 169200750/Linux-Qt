#include "widget.h"
#include "first.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    First w;
    w.show();
    return a.exec();
}
