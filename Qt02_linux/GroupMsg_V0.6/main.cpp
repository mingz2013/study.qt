#include "widget.h"
#include <QApplication>
#include "globalset.h"
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));


    Widget w;

    //MainDockWidget mainWidget;

    //w.mainWidget = &mainWidget;

    // 窗口显示后执行的槽
    //QObject::connect(&w, SIGNAL(mainWidgetShow_signals()), &mainWidget, SLOT(mainWidgetShowSlots()));

    w.show();

    return a.exec();
}
