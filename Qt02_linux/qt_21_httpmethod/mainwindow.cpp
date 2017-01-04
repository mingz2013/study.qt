#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    http = new httpMethod(this);
    connect(http->mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QNetworkCookie cookie;
    cookie.setName("chkuin");
    cookie.setValue("xxx");
    QList<QNetworkCookie> list;
    list.append(cookie);
    QVariant var;
    var.setValue(list);
    QUrl url("https://ssl.ptlogin2.qq.com/check?uin=xxx&appid=1003903&js_ver=10036&js_type=0&login_sig=JUC4UNyS3Wp9UNN9x1NYFENqynWvoZ5pdGeYyBhmJtw6Ptt4xxz4B*tBP51j1W12&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html&r=0.5420278559534947");
    http->sendRequest(url,var );

    //qDebug() << http->reply->readAll();
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply->readAll();// reply读出来后数据就没了
    qDebug() << http->reply->readAll();//这次就读不出来了
}

void MainWindow::on_pushButton_2_clicked()//    用阻塞的方法。。。。。。。。。。。。。。。。。。。。。。。yes
{
    QNetworkAccessManager *manager;//
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
     request.setUrl(QUrl("http://www.baidu.com"));
    // request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
     QEventLoop loop;
      //  QNetworkReply *reply = manager.head(QNetworkRequest(link));
     QNetworkReply *reply = manager->get(request);          // 这里是直接返回reply的
        //QObject::connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
     connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
        loop.exec();
         qDebug() << reply->readAll();
         reply->deleteLater();

     /*
     connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
      connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
              this, SLOT(slotError(QNetworkReply::NetworkError)));
      connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
              this, SLOT(slotSslErrors(QList<QSslError>)));
              */
}
