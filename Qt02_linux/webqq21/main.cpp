#include "widget.h"
#include "maindockwidget.h"
#include <QApplication>
#include "globalset.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget w;

    MainDockWidget mainWidget;

    w.mainWidget = &mainWidget;

    // 窗口显示后执行的槽
    QObject::connect(&w, SIGNAL(mainWidgetShow_signals()), &mainWidget, SLOT(mainWidgetShowSlots()));

    w.show();

    return a.exec();
}
