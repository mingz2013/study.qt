#ifndef MSGALERTDIALOG_H
#define MSGALERTDIALOG_H

#include <QDialog>
#include "myjson.h"
#include <QMouseEvent>

namespace Ui {
class MsgAlertDialog;
}

class MsgAlertDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MsgAlertDialog(QJsonObject item_value, bool isButty = true, QWidget *parent = 0);
    ~MsgAlertDialog();
    void setMsg(QJsonObject item_value);

     QString from_uin;
    
private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::MsgAlertDialog *ui;
    QJsonObject item_value;
    bool isButty;



    QPoint windowPos, dPos, mousePos;// 移动相关

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // MSGALERTDIALOG_H
