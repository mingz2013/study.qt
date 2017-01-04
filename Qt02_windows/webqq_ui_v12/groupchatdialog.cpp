#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"
#include <QMouseEvent>
#include "globalset.h"
#include "tools.h"
#include "chatdialog.h"

extern GlobalSet globalset;// 引用全局变量

GroupChatDialog::GroupChatDialog(QVariant var,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDialog)
{
    ui->setupUi(this);
    this->var_groupChatDialog = var;
    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    Init();
}

GroupChatDialog::~GroupChatDialog()
{
    delete ui;
}

void GroupChatDialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
}

void GroupChatDialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

/**
 *初始化
**/
void GroupChatDialog::Init()
{
    // ui->label_avatar->setGeometry(5, 5, 60, 60);
    //  setLayout();
    connect(globalset.webqq, SIGNAL(group_info_Signal(QJsonObject)), this, SLOT(webqq_group_info_Slot(QJsonObject)));


    msg_id = 87000001;


    QString code = QString::number((qulonglong)var_groupChatDialog.toJsonObject().value("code").toDouble());
    globalset.webqq->get_group_info_ext2(code);// 获取群列表
    group_uin = QString::number((qulonglong)var_groupChatDialog.toJsonObject().value("gid").toDouble());



}



void GroupChatDialog::on_pushButton_Minisize_clicked()
{
    this->setHidden(true);
}

void GroupChatDialog::on_pushButton_Close_clicked()
{
    this->close();
}

/**
 *发送消息按钮单击槽
**/
void GroupChatDialog::on_pushButton_sendMsg_clicked()
{
    if(ui->plainTextEdit_editor->toPlainText().trimmed().isEmpty()){
        qDebug() << "发送内容为空";
        return;
    }

    qDebug() << "发送群消息";
    globalset.webqq->post_send_qun_msg2(group_uin, ui->plainTextEdit_editor->toPlainText());   // 发送群消息

    qDebug() << "发送信息 post方法";
    qDebug() << ui->plainTextEdit_editor->toPlainText();
    QString title = globalset.webqq->nick + " " + Tools::getTimeNow();
    QString content = ui->plainTextEdit_editor->toPlainText();
    ui->textBrowser_msgList->append(title + "\n" + "   " + content + "\n");// 显示在列表
    ui->plainTextEdit_editor->setPlainText("");         // 清空输入框

}

/**
 *窗口关闭事件
 *窗口关闭之前所做的工作
**/
void GroupChatDialog::closeEvent(QCloseEvent *event)
{
    globalset.other_struct.groupDialog_List.removeOne(this);

    GroupChatDialog::closeEvent(event);
}

/**
 *获取群信息和群好友列表的槽
**/
void GroupChatDialog::webqq_group_info_Slot(QJsonObject obj)
{

    QJsonArray stats = obj.value("result").toObject().value("stats").toArray();
    minfo = obj.value("result").toObject().value("minfo").toArray();
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
void GroupChatDialog::on_listWidget_GroupList_itemPressed(QListWidgetItem *item)
{
    if (qApp->mouseButtons() == Qt::LeftButton)
    {
        ChatDialog* chatDialog_it;
        foreach (chatDialog_it, globalset.other_struct.chatDialog_List){
            if(chatDialog_it->var_chatDialog == item->data(Qt::UserRole)){
                // 如果窗口已打开，则将其获取焦点----------------------------------------???????????????????????????
                setFocusProxy(chatDialog_it);
                return;
            }
        }
        // 如果窗口未打开，则打开窗口，并加入列表
        ChatDialog *chatDialog = new ChatDialog(item->data(Qt::UserRole), false);
        globalset.other_struct.chatDialog_List.insert(0, chatDialog);
        chatDialog->show();
    }

}

void GroupChatDialog::on_pushButton_Close_2_clicked()
{
    this->close();
}

/**
 *接收群消息的槽
**/
void GroupChatDialog::group_message_Slot(QJsonObject value)
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

