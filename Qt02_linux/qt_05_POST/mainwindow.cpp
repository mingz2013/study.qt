#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QDebug>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    /*/ 参数设置*/
    // url地址
    QUrl url("https://passport.baidu.com/v2/api/?login");
    // 数据内容
    QByteArray append("staticpage=http%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fv3Jump.html&charset=UTF-8&token=66dd228dfe0b020f0d1bc6cedaa3edbf&tpl=mn&apiver=v3&tt=1374748196503&codestring=&isPhone=false&safeflg=0&u=http%3A%2F%2Fwww.baidu.com%2F&quick_user=0&username=mingzznet&password=let250976&verifycode=&mem_pass=on&ppui_logintime=17253&callback=parent.bd__pcbs__8feo69");
    // 数据长度
    int appendLength = append.length();

    /*构造请求*/
    // 声明一个请求
    QNetworkRequest request;
    // 设置地址
    request.setUrl(url);
    qDebug() << url;
    // 设置头部信息
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader,appendLength);

    //request.setAttribute();// QNetworkRequest和QNetworkReply的属性编码。

    /*post数据*/
    //QNetworkReply* reply = nam->get(QNetworkRequest(url));
    QNetworkReply* reply = manager->post(request, append);

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
           QByteArray bytes = reply->readAll();  // bytes
           //QString string(bytes); // string
           QString string = QString::fromUtf8(bytes);

           ui->textBrowser->setText(string);
           qDebug() << tr("string的");
           qDebug() << string;
    }
       // Some http error received
    else
    {
           // handle errors here
        qDebug() << "reply->error()";
        qDebug() << reply->error();

    }

       // We receive ownership of the reply object
       // and therefore need to handle deletion.
      reply->deleteLater();
      qDebug() << "reply->deletelater()";
}
