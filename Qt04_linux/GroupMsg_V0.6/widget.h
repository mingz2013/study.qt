#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "httpmethod.h"
#include "tools.h"
#include "verifylabel.h"
#include "myjson.h"
#include "poll2thread.h"

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



signals:
    void group_message_Signal(QJsonObject value);// 群消息
    
private slots:

    void on_pushButton_login_clicked();     // 登录按钮被单击

    void on_label_imgverify_Clicked(verifyLabel *);// imglabel被单击

    void on_label_changeimg_link_Clicked(verifyLabel *);// changimg label被单击

    void on_lineEdit_password_focusInSignal();// 密码框获取焦点

    void on_lineEdit_QQNumber_focusOutSignal();// QQ号输入框失去焦点

    void poll2ThreadSlots(QString context);// 线程槽函数

    void group_message_Slot(QJsonObject value);// 群消息

    void on_spinBox_low_valueChanged(int arg1);

    void on_spinBox_high_valueChanged(int arg1);

    void on_textEdit_keys_textChanged();

    void on_textEdit_hackwords_textChanged();

    void on_textEdit_replease_textChanged();

    void on_lineEdit_replease_word_textChanged(const QString &arg1);

    void on_textEdit_tel_textChanged();

private:
    Ui::Widget *ui;
    // 变量
    httpMethod *httpmethod; // httpMethod类
    poll2Thread *poll2thread;
    bool hadGetverifycode ; // 当前QQ号是否获取了文字验证码
    QString textCode;       // 文字验证码
    QString textCode_write; // 输入的验证码

    QString pt_uin; // 16进制串

    //QString getpt4_302_url;
    QString getcheck_sig_url;

    int length_low;// 信息长度控制
    int length_high;
    QStringList key_list;// 关键字列表
    QStringList hackword_list;// 黑名单列表
    QStringList repleaseword_list;// 被替换的关键字
    QString replease_word;  // 用于替换的字符
    QStringList tel_list;   // 电话列表
    QList<QJsonObject> Groupinfo_list;// 群好友列表 的 列表




    // 方法
    void Init();    // 初始化函数
    void need_verifycode(bool need);    // 需要或不许要验证码框的显示和隐藏
    void loginhide();   // 登录控件隐藏
    void set_showText(QString text = NULL);    // 顶端提示消息
    void set_Log(QString text = NULL);      // 日志记录

    bool getverifycode();   // 获取验证码令牌
    void getverifyimg();    // 获取并显示 验证码图片
    bool getlogin();        // getlogin方法
    //void getpt4_302();      //
    void getcheck_sig();    //
    void postlogin();       // postlogin方法
    void post_get_group_name_list_mask2();// 获取群列表和标记

    QString get_number(QString uin, QString type);  // 获取好友QQ号
    void get_group_info_ext2(QString code); // 获取群好友列表
    bool get_send_to_website(QString Msg_Content, QString Msg_Tel, QString Msg_Company); // get提交到指定的服务器

    void saveLog(); // 关闭前保存日志
    void writeSettings();// 写配置
    void readSettings();// 读配置
    void closeEvent(QCloseEvent *e);// 关闭事件

};

#endif // WIDGET_H
