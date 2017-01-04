#ifndef CHATBOX_DOCKWIDGET_H
#define CHATBOX_DOCKWIDGET_H

#include <QDockWidget>
#include <QVariant>
#include <QCloseEvent>
#include "myjson.h"
#include <QListWidgetItem>

namespace Ui {
class chatBox_DockWidget;
}

class chatBox_DockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit chatBox_DockWidget(QVariant var, bool isButty = true, QWidget *parent = 0);
    ~chatBox_DockWidget();

    QVariant var_chatBox;
    
private slots:
    void on_pushButton_sendMsg_clicked();// 发送按钮单击槽

    void on_listWidget_GroupList_itemPressed(QListWidgetItem *item);

    void message_Slot(QJsonObject value);
    void group_message_Slot(QJsonObject value);
    void webqq_group_info_Slot(QJsonObject obj);

protected:
    void closeEvent(QCloseEvent *event);// 关闭事件函数
    void resizeEvent(QResizeEvent *event);   // 窗体尺寸改变事件

private:
    Ui::chatBox_DockWidget *ui;
    bool isButty;
    QJsonObject ginfo;
    QJsonArray minfo;
    int msg_id; // 消息标号
    QString group_uin ;
    QString uin ;
    QString nick;

    void Init();    // 初始化
    void setLayout(); // 处理界面



};

#endif // CHATBOX_DOCKWIDGET_H
