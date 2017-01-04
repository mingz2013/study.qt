#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mManager = new QNetworkAccessManager(this);
    mManager->setCookieJar(new QNetworkCookieJar(this));
    connect(mManager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl url("https://passport.baidu.com/v2/api/?login"); // https and http are both allowed.
    QByteArray postData;
    postData.append("staticpage=http%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fv3Jump.html&charset=UTF-8&token=66dd228dfe0b020f0d1bc6cedaa3edbf&tpl=mn&apiver=v3&tt=1375106224350&codestring=&isPhone=false&safeflg=0&u=http%3A%2F%2Fwww.baidu.com%2F&quick_user=0&username=mingzznet&password=let250976&verifycode=&mem_pass=on&ppui_logintime=17040&callback=parent.bd__pcbs__qh89hl");
    sendPostRequest(url, postData);
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QNetworkCookie>  cookies = mManager->cookieJar()->cookiesForUrl(mUrl);
    QVariant var;
    var.setValue(cookies);

    QNetworkRequest r(QUrl("http://www.baidu.com"));
    r.setHeader(QNetworkRequest::CookieHeader, var);
    mManager->get(r);
}
