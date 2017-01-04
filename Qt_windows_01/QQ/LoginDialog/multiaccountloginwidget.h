#ifndef MULTIACCOUNTLOGINWIDGET_H
#define MULTIACCOUNTLOGINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>

#include "headwidget.h"
#include "pushbutton.h"

class MultiAccountLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MultiAccountLoginWidget(QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    void sureAdd_clicked();
    void cancel_clicked();
public slots:

private:
    void createUI();
    void setUILayout();
    void setConnect();
    
private:
    HeadWidget *headWidget;

    QComboBox *usernameComboBox;
    QLineEdit *passwordLineEdit;

    PushButton *keyboardButton;

    PushButton *sureAddButton;
    PushButton *cancelButton;

    QString initUsernameText;
    QString initPasswordText;
};

#endif // MULTIACCOUNTLOGINWIDGET_H
