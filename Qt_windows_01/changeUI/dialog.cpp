#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
     ui->pushButton_A->setHidden(true);
      ui->pushButton_B->setHidden(true);
       ui->pushButton_C->setHidden(true);

       isLock = true;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_A_Close_clicked()
{
    ui->widget_A->setHidden(true);
    ui->pushButton_A->setHidden(false);
}

void Dialog::on_pushButton_B_Close_clicked()
{
    ui->widget_B->setHidden(true);
    ui->pushButton_B->setHidden(false);
}

void Dialog::on_pushButton_C_Close_clicked()
{
    ui->widget_C->setHidden(true);
    ui->pushButton_C->setHidden(false);
}

void Dialog::on_pushButton_A_clicked()
{
    ui->widget_A->setHidden(false);
    ui->pushButton_A->setHidden(true);
}

void Dialog::on_pushButton_B_clicked()
{
    ui->widget_B->setHidden(false);
    ui->pushButton_B->setHidden(true);
}

void Dialog::on_pushButton_C_clicked()
{
    ui->widget_C->setHidden(false);
    ui->pushButton_C->setHidden(true);
}

void Dialog::on_pushButton_SYS_Close_clicked()
{
    this->close();
}

void Dialog::on_pushButton_Lock_clicked()
{
    if(isLock){
        ui->pushButton_Lock->setStyleSheet("border-image: url(:/res/res/unlock.jpg);");
        isLock = false;
    }else{
        ui->pushButton_Lock->setStyleSheet("border-image: url(:/res/res/lock.jpg);");
        isLock = true;
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
   // ui->widget_A->move(event->globalPos() - ui->widget_A->pos());
}

void Dialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}
