#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    http = new httpMethod(this);
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
    QNetworkReply * reply = http->sendRequest(url,var );
    qDebug() << reply->readAll();
    reply->deleteLater();
}
