#include "widget.h"
#include "maindockwidget.h"
#include <QApplication>
#include <Init.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    MainDockWidget MainWidget;
    MainWidget.w = &w;
    w.maindockwidget = &MainWidget;

    w.show();
    
    return a.exec();
}
