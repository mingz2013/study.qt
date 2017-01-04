#include "widget.h"
#include "ui_widget.h"
#include <QDialog>

extern int num ;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
num = 10;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //MainDockWidget *MainWidget = new MainDockWidget();
    //MainWidget->show();
    maindockwidget->show();
    //this->close();
    //MainDockWidget MainWidget(this);
    //MainWidget.exec();
    //if (MainWidget.result() == QDialog::Accepted) {}

}
