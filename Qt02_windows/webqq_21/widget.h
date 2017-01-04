#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "tools.h"
#include "verifylabel.h"
#include "webqq.h"

/**
 *登录窗体
**/
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    // 变量
    QWidget *mainWidget;// 主窗口指针

signals:
    void mainWidgetShow_signals();
    
private slots:

    void on_pushButton_login_clicked();     // 登录按钮被单击

    void on_label_imgverify_Clicked(verifyLabel *);// imglabel被单击

    void on_label_changeimg_link_Clicked(verifyLabel *);// changimg label被单击


    void on_lineEdit_QQNumber_focusOutSignal();

    void on_lineEdit_password_focusInSignal();

private:
    Ui::Widget *ui;



    // 方法
    void Init();    // 初始化函数
    void need_verifycode(bool need);    // 需要或不许要验证码框的显示和隐藏
    void set_showText(QString text = NULL);    // 顶端提示消息
};

#endif // WIDGET_H
