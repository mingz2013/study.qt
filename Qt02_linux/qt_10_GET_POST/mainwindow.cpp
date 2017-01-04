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
    QUrl url("https://passport.baidu.com/v2/api/?login"); // https and http are both allowed.
    QByteArray postData;
    postData.append("staticpage=http%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fv3Jump.html&charset=UTF-8&token=66dd228dfe0b020f0d1bc6cedaa3edbf&tpl=mn&apiver=v3&tt=1375106224350&codestring=&isPhone=false&safeflg=0&u=http%3A%2F%2Fwww.baidu.com%2F&quick_user=0&username=mingzznet&password=let250976&verifycode=&mem_pass=on&ppui_logintime=17040&callback=parent.bd__pcbs__qh89hl");


    http->sendRequest(url,NULL, tr("POST"), postData);
    if(http->reply != NULL)
    {
        QVariant var =  http->reply->header(QNetworkRequest::SetCookieHeader);
        QList<QNetworkCookie> cookielist = var.value< QList<QNetworkCookie> >();
        QNetworkCookie cookies;
        foreach (cookies, cookielist)
        {
            qDebug()<< "----------11111111111-----------";
            qDebug()<< cookies.name() << "--------------->" << cookies.value();
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
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
}

void MainWindow::on_pushButton_3_clicked()
{
    QUrl url("https://passport.baidu.com/v2/api/?logincheck&token=db0cb29888b0aabbd04b853e3ca67baa&tpl=pcs&apiver=v3&tt=1375165779529&username=xxx%40qq.com&isphone=false&callback=bd__cbs__p13ax4");
    http->sendRequest(url);
}

void MainWindow::on_pushButton_4_clicked()
{
    //QNetworkReply *reply = http->getReply();
   // QNetworkReply *reply = http->reply;

   /*
     if(http->reply != NULL)
    {
        QList<QNetworkCookie> cookielist = qvariant_cast< QList<QNetworkCookie> >(http->reply->header(QNetworkRequest::SetCookieHeader));



        QNetworkCookie cookies;
        foreach (cookies, cookielist)
        {
            qDebug()<< "----------11111111111-----------";
            qDebug()<< cookies.name() << "--------------->" << cookies.value();

        }
    }
*/
    QNetworkCookie cookie;

    QList<QNetworkCookie> list;

    cookie.setName("chkuin");
    cookie.setValue("xxx");
    list.append(cookie);

    cookie.setName("hahahaha");
    cookie.setValue("xxx");
    list.append(cookie);

    qDebug() << "list-------->" << list;

    QNetworkCookie cookies;
    foreach (cookies, list)
    {
        qDebug()<< "----------11111111111-----------";
        qDebug()<< cookies.name() << "--------------->" << cookies.value();

    }

    QVariant var;
    var.setValue(list);
    qDebug() << "var------------>" << var;
    /*
    QUrl url("https://ssl.ptlogin2.qq.com/check?uin=xxx&appid=1003903&js_ver=10036&js_type=0&login_sig=JUC4UNyS3Wp9UNN9x1NYFENqynWvoZ5pdGeYyBhmJtw6Ptt4xxz4B*tBP51j1W12&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html&r=0.5420278559534947");
    http->sendRequest(url,var );
    */
}
