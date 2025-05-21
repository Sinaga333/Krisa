#include "mainwindow.h"

#include <QApplication>
#include <start.h>>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start s;
    s.show();
    MainWindow w(&s);
    return a.exec();
}
