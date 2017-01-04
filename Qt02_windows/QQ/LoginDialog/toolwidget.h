#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

#include "pushbutton.h"

class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    void setting_clicked();
    void minimize_clicked();
    void close_clicked();

public slots:

private:
    void createUI();
    void setUILayout();
    void setConnect();
    
private:
    PushButton *settingButton;
    PushButton *minimizeButton;
    PushButton *closeButton;
};

#endif // TOOLWIDGET_H
