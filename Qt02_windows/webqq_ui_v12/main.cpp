#include <QApplication>
#include "logindialog.h"
#include "maindialog.h"
#include "chatdialog.h"
#include "groupchatdialog.h"

#include <QIcon>
#include <QSystemTrayIcon>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSystemTrayIcon *sysTrayIcon = new QSystemTrayIcon();//创建一个系统托盘图标;
    sysTrayIcon->setIcon(QIcon(":/login/Resources/QQ.png"));//定义一个系统托盘图标并设置图标
    sysTrayIcon->show();


    LoginDialog w;
    MainDialog maindialog;
    w.maindialog = &maindialog;
    // 窗口显示后执行的槽
    QObject::connect(&w, SIGNAL(mainDialogShow_signals()), &maindialog, SLOT(mainDialogShowSlots()));

    w.setWindowOpacity(1);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground);

    maindialog.setWindowOpacity(1);
    maindialog.setWindowFlags(Qt::FramelessWindowHint);
    maindialog.setAttribute(Qt::WA_TranslucentBackground);

    w.show();
    
    return a.exec();
}
