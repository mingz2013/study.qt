#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QMouseEvent>
#include "globalset.h"
#include "tools.h"

extern GlobalSet globalset;// 引用全局变量

ChatDialog::ChatDialog(QVariant var,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    this->var_chatDialog = var;
    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

    Init();
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
    QDialog::mouseMoveEvent(event);
}

void ChatDialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;

    QDialog::mousePressEvent(event);
}

/**
 *窗口关闭事件
 *窗口关闭之前所做的工作
**/
void ChatDialog::closeEvent(QCloseEvent *event)
{
    globalset.other_struct.chatDialog_List.removeOne(this);


    QDialog::closeEvent(event);
}

/**
 *初始化
**/
void ChatDialog::Init()
{
    // ui->label_avatar->setGeometry(5, 5, 60, 60);
    // setLayout();
    // connect(globalset.webqq, SIGNAL(group_info_Signal(QJsonObject)), this, SLOT(webqq_group_info_Slot(QJsonObject)));


    msg_id = 87000001;


    // 显示昵称和头像
    nick = var_chatDialog.toJsonObject().value("nick").toString();
    qDebug() << var_chatDialog.toJsonObject();
    qDebug() << "nick------->" << nick;
    ui->label_mainname->setText(nick);
    uin = QString::number((qulonglong)(var_chatDialog.toJsonObject().value("uin").toDouble()));


}

/**
 *发送消息按钮单击槽
**/
void ChatDialog::on_pushButton_sendMsg_clicked()
{
    if(ui->plainTextEdit_editor->toPlainText().trimmed().isEmpty()){
        qDebug() << "发送内容为空";
        return;
    }

    qDebug() << "给好友发送消息";
    globalset.webqq->post_send_buddy_msg2(uin, ui->plainTextEdit_editor->toPlainText()); // 发送消息，post参数还没设置好，先不发呢

    qDebug() << "发送信息 post方法";
    qDebug() << ui->plainTextEdit_editor->toPlainText();
    QString title = globalset.webqq->nick + " " + Tools::getTimeNow();
    QString content = ui->plainTextEdit_editor->toPlainText();
    ui->textBrowser_msgList->append(title + "\n" + "   " + content + "\n");// 显示在列表
    ui->plainTextEdit_editor->setPlainText("");         // 清空输入框

}

void ChatDialog::on_pushButton_Close_clicked()
{
    this->close();
}

void ChatDialog::on_pushButton_Minisize_clicked()
{
    this->setHidden(true);
}

void ChatDialog::on_pushButton_Close_2_clicked()
{
    this->close();
}

/**
 *接收好友消息的槽
**/
void ChatDialog::message_Slot(QJsonObject value)
{
    QString from_uin = QString::number((qulonglong)value.value("from_uin").toDouble());
    if(uin == from_uin){
        QString content_text = value.value("content").toArray().last().toString();
        QString title = nick + " " + Tools::getTimeNow();
        ui->textBrowser_msgList->append(title + "\n" + "   " + content_text + "\n");
    }else{return;}
}
