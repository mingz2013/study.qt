#ifndef MAINDOCKWIDGET_H
#define MAINDOCKWIDGET_H

#include <QDockWidget>
#include "myjson.h"
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include "chatbox_dockwidget.h"
#include "poll2thread.h"

/**
 *主窗体类
**/
namespace Ui {
class MainDockWidget;
}

class MainDockWidget : public QDockWidget
{
    Q_OBJECT

    
public:
    explicit MainDockWidget(QWidget *parent = 0);
    ~MainDockWidget();

signals:
    void message_Signal(QJsonObject value);  // 好友信息
    void group_message_Signal(QJsonObject value);// 群消息


public slots:
    void mainWidgetShowSlots();


private slots:
    void on_treeWidget_BuddyList_itemPressed(QTreeWidgetItem *item, int column);

    //void on_treeWidget_BuddyList_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_GroupList_itemPressed(QListWidgetItem *item);

    void webqq_lnick_Slots(QString lnick);
    void webqq_friends_result_Slots(QJsonObject friends_result);
    void webqq_qun_result_Slots(QJsonObject qun_result);
    void webqq_onlinelist_Slots(QJsonArray onlineList);
    void webqq_poll2_obj_Slots(QJsonObject obj);

private:
    // 变量
    Ui::MainDockWidget *ui;

    QJsonArray info;    // 好友信息
    QJsonArray marknames;
    poll2Thread *poll2thread;



    // 方法
    void Init();    // 初始化
    void resizeEvent(QResizeEvent *e);  // 尺寸改变事件
    void closeEvent(QCloseEvent *event);// 窗口关闭事件




};

#endif // MAINDOCKWIDGET_H
