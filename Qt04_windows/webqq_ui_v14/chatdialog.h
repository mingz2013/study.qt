#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QVariant>
#include "myjson.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChatDialog(QVariant var,QWidget *parent = 0);
    ~ChatDialog();

    QVariant var_chatDialog;
    QString uin;


    
private slots:
    void on_pushButton_Close_clicked();

    void on_pushButton_Minisize_clicked();

    void on_pushButton_sendMsg_clicked();

    void on_pushButton_Close_2_clicked();

    void message_Slot(QJsonObject value);

private:
    Ui::ChatDialog *ui;

    QPoint windowPos, dPos, mousePos;

    int msg_id;
    QString nick;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);



    void Init();
};

#endif // CHATDIALOG_H
