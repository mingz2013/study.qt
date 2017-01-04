#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication::setStyle("cleanlooks");

    QApplication a(argc, argv);
    Widget w;

  //  w.setAutoFillBackground(true);

  //  QPalette palette;

    //palette.setColor(QPalette::Background, QColor(192,253,123));
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/1.png")));

//w.setPalette(palette);

   // w.setWindowOpacity(0.5);
   // w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setAttribute(Qt::WA_TranslucentBackground);






    w.show();
    
    return a.exec();
}
