#include "mainwindow.h"
#include <QApplication>
#include <QMutex>


int p[10];
int i = 0;
int a = 0;
QMutex mutex;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
