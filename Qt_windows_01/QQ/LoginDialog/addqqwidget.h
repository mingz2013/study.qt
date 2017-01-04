#ifndef ADDQQWIDGET_H
#define ADDQQWIDGET_H

#include <QWidget>
#include "pushbutton.h"

class AddQQWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddQQWidget(QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    void singleAccountLogin_clicked();
    void multiAccountLogin_clicked();
    void qrCode_clicked();
public slots:
private:
    void createUI();
    void setUILayout();
    void setConnect();
private:
    PushButton *addQQButton;

    PushButton *singleAccountLoginButton;
    PushButton *loginButton;
    PushButton *qrCodeLoginButton;
};

#endif // ADDQQWIDGET_H
