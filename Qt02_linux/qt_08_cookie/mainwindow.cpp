#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));

    //-------------------------------------------
    networkCookieJar = new QNetworkCookieJar(this);
    manager->setCookieJar(networkCookieJar);
    //-----------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl url;
    url.setUrl("http://www.baidu.com");

    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply;
    reply = manager->get(request);

    //--------------------------------------------------
    QNetworkCookie cookie;
    //QList<QNetworkCookie> list = networkCookieJar->cookiesForUrl(QUrl("http://xxx.com/"));
    QList<QNetworkCookie> list = networkCookieJar->cookiesForUrl(url);
    qDebug()<< "-----------*******************";
    foreach (cookie ,list)
    {
        qDebug()<< "---------------------";
        qDebug()<< cookie.name();
        qDebug()<< cookie.value();
    }
    qDebug() << list;
    qDebug()<< "-----------*******************";
    //------------------------------------------------------
}

void MainWindow::replyFinish(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();

        QString string = QString::fromUtf8(bytes);

        ui->textBrowser->setText(string);

        qDebug() << string;

    }
    else
    {
        qDebug() << "reply error";
    }

    reply->deleteLater();
}

