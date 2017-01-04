#include "systemtray.h"
#include <QApplication>

#include <QCoreApplication>

SystemTray::SystemTray(QWidget *w, const QString &iconFileName) :
    QObject(), widget(w)
{
    icon = QIcon(iconFileName);
    createMenu();
    createTrayIcon();
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &SystemTray::iconActivated);

    retranslateUI();
}

void SystemTray::createMenu()
{
    showAction = new QAction(widget);
    connect(showAction, &QAction::triggered, widget, &QWidget::showNormal);

    quitAction = new QAction(widget);
    //connect(quitAction, &QAction::triggered, this, &SystemTray::quitTriggered);//编译错误
    connect(quitAction, &QAction::triggered, &QApplication::quit);//新的connect写法，允许省略接受者

    //注意：trayIconMenu的父类为desktop，如果为this,则右键单击托盘不选中时，托盘菜单不消失。
    trayIconMenu = new QMenu((QWidget*)QApplication::desktop());

    //此处使用QSS的原因，trayIconMenu不是this的子窗口,qApp.setStyleSheet(qss.readAll());才可进行设置
    //此处为了方遍，直接使用
    trayIconMenu->setStyleSheet("QMenu{font-size: 12px;"
                                "border-image:url(:/menu/menu_bg) 4 50 4 1 repeat-y;}");

    trayIconMenu->addAction(showAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void SystemTray::retranslateUI()
{
    showAction->setText(tr("show"));
    quitAction->setText(tr("quit"));
}

void SystemTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger: //单击
    case QSystemTrayIcon::DoubleClick://双击
        widget->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:

        break;
    default:
        ;
    }
}

void SystemTray::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Tray tool tip");
}

void SystemTray::setTrayIcon(const QString &iconFileName)
{
    trayIcon->setIcon(QIcon(iconFileName));
}

void SystemTray::setToolTip(const QString &tip)
{
    trayIcon->setToolTip(tip);
}
