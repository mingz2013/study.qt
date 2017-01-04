#include "widget.h"
#include "ui_widget.h"
#include "myxml.h"
#include "myjson.h"
#include <QSettings>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // MyXml *xml = new MyXml(this);

    //myjson* json = new myjson(this);
    WriteSettings();
    ReadSettings();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::WriteSettings() {
    //QSettings settings("Software Inc", "Spreadsheet"); // windows在注册表中建立建 Software Inc -> Spreadsheet
    QSettings settings("Option.ini", QSettings::IniFormat); // 当前目录的INI文件

    settings.beginGroup("Config");
    settings.setValue("geometry", "aaaaaa");
    settings.setValue("speed", "哈哈哈");
    settings.setValue("CarNum", 40);

    settings.setValue("haha", var);
    settings.endGroup();
}
void Widget::ReadSettings() {
    QSettings settings("Option.ini", QSettings::IniFormat);
    QString speed = settings.value("Config/speed").toString();
    QString CarNum = settings.value("Config/CarNum").toString();
    QString geometry = settings.value("Config/geometry").toString();
    qDebug() << speed << CarNum << geometry;
}
