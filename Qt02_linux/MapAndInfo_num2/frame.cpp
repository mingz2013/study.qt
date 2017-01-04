#include "frame.h"
#include "ui_frame.h"
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Frame::Frame( QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);


}

void Frame::setCity(QString city)
{
    QPixmap pixmap(QString("image/")+city+QString(".jpg"));
    //ui->label_picture->setFixedSize(pixmap.size());
    ui->label_picture->setPixmap(pixmap);
    ui->label_picture->setScaledContents(true);


    ui->plainTextEdit_info->setPlainText(readFile(QString("file/")+city+(".txt")));
}

Frame::~Frame()
{
    delete ui;
}

QString Frame::readFile(const QString& fpath)
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
