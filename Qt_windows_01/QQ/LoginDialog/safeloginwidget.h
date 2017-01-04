#ifndef SAFELOGINWIDGET_H
#define SAFELOGINWIDGET_H

#include <QWidget>
#include <QLabel>

#include "pushbutton.h"

class SafeLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SafeLoginWidget(QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    void cancel_clicked();
public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    void createUI();
    void setUILayout();
    void setConnect();
private:
    QLabel *safeLabel;
    QLabel *titleLabel;

    QLabel *infoLabel;
    QString safeManagerUrl;
    QString knowMoreUrl;

    QLabel *qrCodeLabel;

    PushButton *cancelButton;
};

#endif // SAFELOGINWIDGET_H
