#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "verifylabel.h"
#include "maindialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    MainDialog *maindialog;

    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void mainDialogShow_signals();
    
private slots:
    void on_pushButton_Setting_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Right_clicked();

    void on_pushButton_Minisize_clicked();

    void on_pushButton_Close_clicked();

    void on_lineEdit_Password_focusInSignal();

    void on_label_imgverify_Clicked(verifyLabel *);

    void on_label_ChangeImg_Clicked(verifyLabel *);

    void on_pushButton_Login_clicked();

    void on_lineEdit_QQNumber_focusOutSignal();

private:
    Ui::LoginDialog *ui;
    QPoint windowPos, dPos, mousePos;// 移动相关

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void needVerifyCode(bool need);
    void set_showText(QString text);
};

#endif // LOGINDIALOG_H
