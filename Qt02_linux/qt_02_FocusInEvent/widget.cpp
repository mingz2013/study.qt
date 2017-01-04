#include "widget.h"
#include "ui_widget.h"
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //lineEdit = new MyLineEdit(this, ui->label);
   // lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
   // ui->formLayout->setWidget(0, QFormLayout::SpanningRole, lineEdit);

}

Widget::~Widget()
{
    delete ui;
}






void Widget::on_lineEdit_2_signal1()
{
    ui->label->setText(tr("aaa"));
}

void Widget::on_lineEdit_2_signal2()
{
    ui->label->setText(tr("bbb"));
}
