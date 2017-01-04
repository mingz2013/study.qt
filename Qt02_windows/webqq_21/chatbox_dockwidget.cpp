#include "chatbox_dockwidget.h"
#include "ui_chatbox_dockwidget.h"
#include "globalset.h"
#include <QDebug>
#include "tools.h"

extern GlobalSet globalset;// 引用全局变量

chatBox_DockWidget::chatBox_DockWidget(QVariant var, bool isButty, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::chatBox_DockWidget)
{
    ui->setupUi(this);
    this->var_chatBox = var;
    this->isButty = isButty;
    Init();// 初始化
}



chatBox_DockWidget::~chatBox_DockWidget()
{
    delete ui;
}

/**
 *初始化
**/
void chatBox_DockWidget::Init()
{
    ui->label_avatar->setGeometry(5, 5, 60, 60);
    setLayout();
    connect(globalset.webqq, SIGNAL(group_info_Signal(QJsonObject)), this, SLOT(webqq_group_info_Slot(QJsonObject)));


    msg_id = 87000001;

    if(!isButty){
        QString code = QString::number((qulonglong)var_chatBox.toJsonObject().value("code").toDouble());
        globalset.webqq->get_group_info_ext2(code);// 获取群列表
        group_uin = QString::number((qulonglong)var_chatBox.toJsonObject().value("gid").toDouble());

    }else{
        // 显示昵称和头像
        nick = var_chatBox.toJsonObject().value("nick").toString();
        qDebug() << var_chatBox.toJsonObject();
        qDebug() << "nick------->" << nick;
        ui->label_mainname->setText(nick);
        uin = QString::number((qulonglong)(var_chatBox.toJsonObject().value("uin").toDouble()));
    }

}

/**
 *窗体尺寸改变事件函数
**/
void chatBox_DockWidget::resizeEvent(QResizeEvent *event)
{
    setLayout();
    QDockWidget::resizeEvent(event);
}

/**
 *处理界面
**/
void chatBox_DockWidget::setLayout()
{
    if(isButty){
        ui->label_mainname->setGeometry(66, 5, ui->dockWidgetContents->width() - 66, 30);
        ui->label_GroupList->hide();
        ui->textBrowser_msgList->setGeometry(5, 66, ui->dockWidgetContents->width() - 5, ui->dockWidgetContents->height() - 66 - 80 - 2 - 40);
        ui->plainTextEdit_editor->setGeometry(5, ui->dockWidgetContents->height() - 80 - 40 - 2, ui->dockWidgetContents->width() - 5, 80);
        ui->listWidget_GroupList->hide();
        ui->pushButton_sendMsg->setGeometry(ui->dockWidgetContents->width() - 85, ui->dockWidgetContents->height() - 33, 85, 28);
        ui->pushButton_close->setGeometry(ui->dockWidgetContents->width() - 85 - 2 - 85, ui->dockWidgetContents->height() - 33, 85, 28);
    }else{
        ui->label_mainname->setGeometry(66, 5, ui->dockWidgetContents->width() - 66 - 126, 30);
        ui->label_GroupList->setGeometry(ui->dockWidgetContents->width() - 125, 5, 120, 20);
        ui->textBrowser_msgList->setGeometry(5, 66, ui->dockWidgetContents->width() - 126 - 5, ui->dockWidgetContents->height() - 66 - 80 - 2 - 40);
        ui->plainTextEdit_editor->setGeometry(5, ui->dockWidgetContents->height() - 80 - 40 - 2, ui->dockWidgetContents->width() - 126 - 5, 80);
        ui->listWidget_GroupList->setGeometry(ui->dockWidgetContents->width() - 125, 5 + 20 + 2, 120, ui->dockWidgetContents->height() - 27 - 5);
        ui->pushButton_sendMsg->setGeometry(ui->dockWidgetContents->width() - 127 - 85, ui->dockWidgetContents->height() - 33, 85, 28);
        ui->pushButton_close->setGeometry(ui->dockWidgetContents->width() - 127 - 85 - 2 - 85, ui->dockWidgetContents->height() - 33, 85, 28);
    }
}

/**
 *窗口关闭事件
 *窗口关闭之前所做的工作
**/
void chatBox_DockWidget::closeEvent(QCloseEvent *event)
{
    if(isButty)
        globalset.other_struct.chatBox_List.removeOne(this);
    else
        globalset.other_struct.groupBox_List.removeOne(this);

    QDockWidget::closeEvent(event);
}

/**
 *发送消息按钮单击槽
**/
void chatBox_DockWidget::on_pushButton_sendMsg_clicked()
{
    if(ui->plainTextEdit_editor->toPlainText().trimmed().isEmpty()){
        qDebug() << "发送内容为空";
        return;
    }
    if(isButty)
    {
        qDebug() << "给好友发送消息";
        globalset.webqq->post_send_buddy_msg2(uin, ui->plainTextEdit_editor->toPlainText()); // 发送消息，post参数还没设置好，先不发呢
    }else{
        qDebug() << "发送群消息";
        globalset.webqq->post_send_qun_msg2(group_uin, ui->plainTextEdit_editor->toPlainText());   // 发送群消息
    }
    qDebug() << "发送信息 post方法";
    qDebug() << ui->plainTextEdit_editor->toPlainText();
    QString title = globalset.webqq->nick + " " + Tools::getTimeNow();
    QString content = ui->plainTextEdit_editor->toPlainText();
    ui->textBrowser_msgList->append(title + "\n" + "   " + content + "\n");// 显示在列表
    ui->plainTextEdit_editor->setPlainText("");         // 清空输入框

}

/**
 *获取群信息和群好友列表的槽
**/
void chatBox_DockWidget::webqq_group_info_Slot(QJsonObject obj)
{

    QJsonArray stats = obj.value("result").toObject().value("stats").toArray();
    QJsonArray minfo = obj.value("result").toObject().value("minfo").toArray();
    QJsonObject ginfo = obj.value("result").toObject().value("ginfo").toObject();

    ui->label_mainname->setText(ginfo.value("name").toString());// 显示群昵称

    for(int row = 0; row < minfo.size(); row++)
    {
       QString nick = minfo[row].toObject().value("nick").toString();
       QListWidgetItem *item = new QListWidgetItem(nick);
       QVariant varData;
       varData.setValue(minfo[row].toObject());
       item->setData(Qt::UserRole, varData);
       ui->listWidget_GroupList->insertItem(0, item);
    }


}





/**
 *群好友列表成员被单击
**/
void chatBox_DockWidget::on_listWidget_GroupList_itemPressed(QListWidgetItem *item)
{
    if (qApp->mouseButtons() == Qt::LeftButton)
    {
        chatBox_DockWidget* chatBox_it;
        foreach (chatBox_it, globalset.other_struct.chatBox_List){
            if(chatBox_it->var_chatBox == item->data(Qt::UserRole)){
                // 如果窗口已打开，则将其获取焦点----------------------------------------???????????????????????????
                setFocusProxy(chatBox_it);
                return;
            }
        }
        // 如果窗口未打开，则打开窗口，并加入列表
        chatBox_DockWidget *chatBox = new chatBox_DockWidget(item->data(Qt::UserRole), false);
        globalset.other_struct.chatBox_List.insert(0, chatBox);
        chatBox->show();
    }

}

/**
 *接收好友消息的槽
**/
void chatBox_DockWidget::message_Slot(QJsonObject value)
{
    QString from_uin = QString::number((qulonglong)value.value("from_uin").toDouble());
    if(uin == from_uin){
        QString content_text = value.value("content").toArray().last().toString();
        QString title = nick + " " + Tools::getTimeNow();
        ui->textBrowser_msgList->append(title + "\n" + "   " + content_text + "\n");
    }else{return;}
}

/**
 *接收群消息的槽
**/
void chatBox_DockWidget::group_message_Slot(QJsonObject value)
{
    QString from_uin = QString::number((qulonglong)value.value("from_uin").toDouble());
    qDebug() << "from_uin--------->" << from_uin;
    if(group_uin == from_uin){
        QString content_text = value.value("content").toArray().last().toString();
        qDebug() << "content_text-------->" << content_text;
        QString send_uin = QString::number((qulonglong)value.value("send_uin").toDouble());
        QString group_butty_nick = send_uin;
        for(int row = 0; row < minfo.size(); row++)
        {
           QString group_butty_uin = QString::number((qulonglong)minfo[row].toObject().value("uin").toDouble());

           if(send_uin == group_butty_uin){
               group_butty_nick = minfo[row].toObject().value("nick").toString();
               qDebug() << "group_butty_nick------------>" << group_butty_nick;
               break;
           }
        }
        QString title = group_butty_nick + " " + Tools::getTimeNow();
        ui->textBrowser_msgList->append(title + "\n" + "   " + content_text + "\n");
    }else{return;}

}
