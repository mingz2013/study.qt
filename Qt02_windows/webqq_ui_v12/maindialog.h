#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "myjson.h"
#include <QTreeWidgetItem>
#include <QListWidgetItem>


namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

public slots:
    void mainDialogShowSlots();
    
private slots:
    void on_pushButton_Close_clicked();

    void on_pushButton_Minisize_clicked();

    void webqq_lnick_Slots(QString lnick);
    void webqq_friends_result_Slots(QJsonObject friends_result);
    void webqq_qun_result_Slots(QJsonObject qun_result);
    void webqq_onlinelist_Slots(QJsonArray onlineList);
    void webqq_poll2_obj_Slots(QJsonObject obj);

    void on_treeWidget_BuddyList_itemPressed(QTreeWidgetItem *item, int column);

    void on_listWidget_GroupList_itemPressed(QListWidgetItem *item);



signals:
    void message_Signal(QJsonObject value);  // 好友信息
    void group_message_Signal(QJsonObject value);// 群消息

private:
    Ui::MainDialog *ui;
    QPoint windowPos, dPos, mousePos;

    QJsonArray info;    // 好友信息
    QJsonArray marknames;



    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

    void Init();
};

#endif // MAINDIALOG_H
