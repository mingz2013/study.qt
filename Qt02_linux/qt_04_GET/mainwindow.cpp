#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建一个管理器
    manager = new QNetworkAccessManager(this);

    //连接请求结束信号
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 1: Creating QImage from the reply
        //QImageReader imageReader(reply);
        //QImage pic = imageReader.read();

        // Example 2: Reading bytes form the reply

        /*/使用utf8编码，这样才可以显示中文
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString all = codec->toUnicode(reply->readAll());
        */

        QByteArray bytes = reply->readAll();  // bytes  
        //QString string(bytes); // string
        QString string = QString::fromUtf8(bytes);

        ui->textBrowser->setText(string);

        qDebug() << string;

        reply->deleteLater();   //最后要释放reply对象
    }
    // Some http error received
    else
    {
        // handle errors here
    }


}


void MainWindow::on_pushButton_clicked()
{
    //创建一个请求
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.baidu.com"));

    //发送GET请求
    QNetworkReply *reply = manager->get(request);

    //连接响应时返回数据信号
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void MainWindow::on_readyRead()
{

}

