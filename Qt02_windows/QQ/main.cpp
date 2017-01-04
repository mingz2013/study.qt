
#include <QApplication>
#include <QTranslator>
#include <QFile>

#include "LoginDialog/logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/qm/QQ_zh");
    a.installTranslator(&translator);

    QFile qss(":/qss/logindialog.qss");
    qss.open(QFile::ReadOnly);

    LoginDialog w;

    QFont font(QObject::tr("Times"));
    w.setFont(font);

    w.setStyleSheet(qss.readAll());
    w.show();

    qss.close();
    
    return a.exec();
}
