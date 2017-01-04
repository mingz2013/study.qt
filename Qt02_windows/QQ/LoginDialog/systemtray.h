#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QWidget>
#include <QSystemTrayIcon>

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QWidget *w, const QString &iconFileName);
    
    void setTrayIcon(const QString &iconFileName);
    void setToolTip(const QString &tip);

    virtual void retranslateUI();
signals:

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
private:
    QWidget *widget;

    QIcon icon;
    QSystemTrayIcon *trayIcon;

    QAction *showAction;
    QAction *quitAction;

protected:
    QMenu *trayIconMenu;
    virtual void createMenu();
private:
    void createActions();
    void createTrayIcon();
};

#endif // SYSTEMTRAY_H
