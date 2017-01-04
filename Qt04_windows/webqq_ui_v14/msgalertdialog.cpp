#include "msgalertdialog.h"
#include "ui_msgalertdialog.h"
#include "globalset.h"






extern GlobalSet globalset;// 引用全局变量

MsgAlertDialog::MsgAlertDialog(QJsonObject item_value, bool isButty,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgAlertDialog)
{
    ui->setupUi(this);
    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->item_value = item_value;
    this->isButty = isButty;
    from_uin = QString::number((qulonglong)item_value.value("from_uin").toDouble());
    if(isButty){
        QString content_text = item_value.value("content").toArray().last().toString();
        ui->textEdit_Msg->setText(content_text);
        ui->label_MainName->setText(from_uin);
    }else{
        QString content_text = item_value.value("content").toArray().last().toString();
        ui->textEdit_Msg->setText(content_text);
        ui->label_MainName->setText(from_uin);
    }

}

MsgAlertDialog::~MsgAlertDialog()
{
    delete ui;
}

void MsgAlertDialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
    QDialog::mouseMoveEvent(event);
}

void MsgAlertDialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
    QDialog::mousePressEvent(event);
}

void MsgAlertDialog::on_pushButton_Close_clicked()
{
    this->close();
}

void MsgAlertDialog::setMsg(QJsonObject item_value)
{
    this->item_value = item_value;
    if(isButty){
        QString content_text = item_value.value("content").toArray().last().toString();
        ui->textEdit_Msg->setText(content_text);
        //ui->label_MainName->setText(from_uin);
    }else{
        QString content_text = item_value.value("content").toArray().last().toString();
        ui->textEdit_Msg->setText(content_text);
        //ui->label_MainName->setText(from_uin);
    }
}

void MsgAlertDialog::closeEvent(QCloseEvent *event)
{
    globalset.other_struct.msgAlertDialog_List.removeOne(this);
    QDialog::closeEvent(event);
}
