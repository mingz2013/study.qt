#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QStackedWidget>
#include <QMouseEvent>

#include "systemtray.h"
#include "backgroundwidget.h"
#include "toolwidget.h"

#include "loginwidget.h"
#include "addqqwidget.h"
#include "multiaccountloginwidget.h"
#include "safeloginwidget.h"

/**
 * @brief The LoginDialog class
 * QQ LoginDialog
 * zdd
 * zddmail@gmail.com
 * Just for fun.
 * 类结构参见博客：http://blog.csdn.net/zddblog/article/details/11098911
 */
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    
    //响应层Widget类型
    enum WidgetType {
        Login,
        AddQQ,
        MultiAccountLogin,
        SafeLogin
    };

signals:
    
public slots:
    void showLoginWidget();
    void showAddQQWidget();
    void showMultiAccountLoginWidget();
    void showSafeLoginWidget();

protected:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    QPoint lastPoint;
    bool isLeftPressed;

private:
    void setUILayout();
    void setConnect();
private:
    LoginWidget *loginWidget;
    AddQQWidget *addQQWidget;
    MultiAccountLoginWidget *multiAccountLoginWidget;
    SafeLoginWidget *safeLoginWidget;

    QStackedWidget *stackedWidget;
    BackgroundWidget *backGroundWidget;
    SystemTray *systemTray;
    ToolWidget *toolWidget;
};

#endif // LOGINDIALOG_H
