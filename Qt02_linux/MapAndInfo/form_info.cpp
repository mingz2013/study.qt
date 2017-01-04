#include "form_info.h"
#include "ui_form_info.h"
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Form_Info::Form_Info(QString city, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Info)
{
    ui->setupUi(this);

    QPixmap pixmap(QString("image/")+city+QString(".jpg"));
    //ui->label_picture->setFixedSize(pixmap.size());
    ui->label_picture->setPixmap(pixmap);
    ui->label_picture->setScaledContents(true);


    ui->plainTextEdit_info->setPlainText(readFile(QString("file/")+city+(".txt")));


}

Form_Info::~Form_Info()
{
    delete ui;
}

QString Form_Info::readFile(const QString& fpath)
{
    if(fpath.isEmpty())
        return "";

    QFile file(fpath);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open file failure!";
        return "";
    }
    QTextStream fs(&file);
    QString fileContent (fs.readAll());

    return fileContent;
}

