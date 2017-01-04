#include "httpmethod.h"
#include <QUrl>




httpMethod::httpMethod(QObject *parent) :
    QObject(parent)
{
    myCookieJar = new MyCookieJar(this);
    mManager = new QNetworkAccessManager(this);
    mManager->setCookieJar(myCookieJar);

    /*/  设置代理
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("202.206.32.248");
    proxy.setPort(80);
    //proxy.setUser("username");
    //proxy.setPassword("password");
    //QNetworkProxy::setApplicationProxy(proxy);
    mManager->setProxy(proxy);
    */
}
httpMethod::~httpMethod(){}




/**
 *参数名：POSTMethod
 *  参数1：QNetworkRequest类型
 *  参数2：QByteArray类型 post数据
 *  返回值：Qnetworkreply类型
 *  作用：执行post方法，返回reply
**/
QNetworkReply* httpMethod::POSTMethod(const QString url, const QByteArray &postData, const QString referer)
{
    QNetworkReply *reply = NULL;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.length());  // 设置数据的长度
    QByteArray byteReferer;
    byteReferer.append(referer);
    request.setRawHeader("Referer", byteReferer);

    QEventLoop loop;
    reply = mManager->post(request, postData);
    connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
    loop.exec();

    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return NULL;
    }
    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    myCookieJar->setCookies(cookielist);
    return reply;

}

/**
 *函数名：GETMethod
 *  参数1：QNetworkRequest类指针
 *  作用：GET方法
**/
QNetworkReply* httpMethod::GETMethod(const QString url, const QString referer)
{
    qDebug() << "in httpMethod :: getmethod";
    QNetworkReply *reply = NULL;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QByteArray byteReferer;
    byteReferer.append(referer);
    request.setRawHeader("Referer", byteReferer);

    QEventLoop loop;
    reply = mManager->get(request);
    connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
    loop.exec();

    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return NULL;
    }
    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    myCookieJar->setCookies(cookielist);
    return reply;
}
