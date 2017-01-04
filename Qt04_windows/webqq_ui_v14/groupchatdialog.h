#ifndef GROUPCHATDIALOG_H
#define GROUPCHATDIALOG_H

#include <QDialog>
#include <QVariant>
#include "myjson.h"
#include <QListWidgetItem>

namespace Ui {
class GroupChatDialog;
}

class GroupChatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GroupChatDialog(QVariant var,QWidget *parent = 0);
    ~GroupChatDialog();

    QVariant var_groupChatDialog;
    QString group_uin;


    
private slots:
    void on_pushButton_Minisize_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_sendMsg_clicked();

    void webqq_group_info_Slot(QJsonObject obj);
    void on_listWidget_GroupList_itemPressed(QListWidgetItem *item);

    void on_pushButton_Close_2_clicked();

    void group_message_Slot(QJsonObject value);

private:
    Ui::GroupChatDialog *ui;

    QPoint windowPos, dPos, mousePos;

    int msg_id;

    QJsonArray minfo;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);




    void Init();
};

#endif // GROUPCHATDIALOG_H
