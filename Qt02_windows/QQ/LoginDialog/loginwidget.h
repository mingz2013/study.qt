#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

#include "pushbutton.h"
#include "headwidget.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    void multiAccount_clicked();
    void login_clicked();
    void qrCode_clicked();
public slots:

private:
    void createUI();
    void setUILayout();
    void setConnect();
private:
    HeadWidget *headWidget;

    QComboBox *usernameComboBox;
    QLineEdit *passwordLineEdit;

    QCheckBox *rememberPasswordCheckBox;
    QCheckBox *autoLoginCheckBox;

    PushButton *registerButton;
    PushButton *findBackPasswordButton;

    PushButton *keyboardButton;

    QString initUsernameText;
    QString initPasswordText;

    PushButton *multiAccountLoginButton;
    PushButton *loginButton;
    PushButton *qrCodeLoginButton;
};

#endif // LOGINWIDGET_H
