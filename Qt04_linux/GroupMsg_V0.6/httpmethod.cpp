#include "httpmethod.h"



httpMethod::httpMethod(QObject *parent) :
    QObject(parent)
{
    mManager = new QNetworkAccessManager(this);
    mManager->setCookieJar(new QNetworkCookieJar(this));
}
httpMethod::~httpMethod(){}


/**
 *方法名称：sendRequest
 *  参数1：QUrl类型 网址
 *  参数2：QVariant类型 封装的cookie列表
 *  参数3：int类型 GET 或 POST 方法
 *  参数4：QByteArray类型 post数据
 *返回值：无
 *作用：发送GET或POST请求，发送Finished信号
**/
QNetworkReply* httpMethod::sendRequest(const QUrl &url,  const QVariant &cookievar,const int method,  const QByteArray &postdata)
{// 发送请求                                            // QVariant 类型设置默认值为空的方法有异常，再查
    QNetworkReply *reply = NULL;
    QNetworkRequest request;
    request.setUrl(url);

    if(!cookievar.isNull())
    {
        request.setHeader(QNetworkRequest::CookieHeader, cookievar);
    }


    if(method == GET)
    {
        qDebug() << "GET method";
        QEventLoop loop;
        reply = mManager->get(request);          // 这里是直接返回reply的
        connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
        loop.exec();
    }
    else if(method == POST)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
        request.setHeader(QNetworkRequest::ContentLengthHeader,postdata.length());  // 设置数据的长度
        //request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2");
        QEventLoop loop;
        reply = mManager->post(request, postdata);
        connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
        loop.exec();
    }
    else
    {
        qDebug() << "method wrong";
    }
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return NULL;
    }
    return reply;
}

/**
 *参数名：POSTMethod
 *  参数1：QNetworkRequest类型
 *  参数2：QByteArray类型 post数据
 *  返回值：Qnetworkreply类型
 *  作用：执行post方法，返回reply
**/
QNetworkReply* httpMethod::POSTMethod(const QNetworkRequest &request, const QByteArray &postData)
{
    QNetworkReply *reply = NULL;

    QEventLoop loop;
    reply = mManager->post(request, postData);
    connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
    loop.exec();

    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return NULL;
    }

    return reply;

}

/**
 *函数名：GETMethod
 *  参数1：QNetworkRequest类指针
 *  作用：GET方法
**/
QNetworkReply* httpMethod::GETMethod(const QNetworkRequest &request)
{
    QNetworkReply *reply = NULL;

    QEventLoop loop;
    reply = mManager->get(request);
    connect(reply,SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);// 用阻塞的方法，非常好
    loop.exec();

    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return NULL;
    }

    return reply;
}
