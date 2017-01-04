#include "httpmethod.h"


httpMethod::httpMethod(QObject *parent) :
    QObject(parent)
{
    reply = NULL;
    mManager = new QNetworkAccessManager(this);
    mManager->setCookieJar(new QNetworkCookieJar(this));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

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
// 发送请求                                            // QVariant 类型设置默认值为空的方法有异常，再查
void httpMethod::sendRequest(const QUrl &url,  const QVariant &cookievar,const int method,  const QByteArray &postdata)
{
    QNetworkRequest request;
    request.setUrl(url);

    if(cookievar != NULL)
    {
        request.setHeader(QNetworkRequest::CookieHeader, cookievar);
    }


    if(method == GET)
    {   qDebug() << "GET method";
        mManager->get(request);

    }
    else if(method == POST)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
        request.setHeader(QNetworkRequest::ContentLengthHeader,postdata.length());  // 设置数据的长度
        mManager->post(request, postdata);
    }
    else
    {
        qDebug() << "method wrong";
    }
}

// reply接收完 槽函数
void httpMethod::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return;
    }
    this->reply = reply;
    //qDebug() << this->reply->readAll();
    //reply->deleteLater();
}

