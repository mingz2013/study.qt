#include "httpmethod.h"

httpMethod::httpMethod(QObject *parent) :
    QObject(parent)
{
    reply = NULL;
    mManager = new QNetworkAccessManager(this);
    mManager->setCookieJar(new QNetworkCookieJar(this));
    connect(mManager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}
httpMethod::~httpMethod(){}

/**
 *sendRequest方法再加一个cookies参数，QList<QNetworkCookie>类型
 *
 *加 一个返回cookies的方法 和 一个返回reply的方法，用于取得上次访问后得到的cookies和reply
 *
 *加一个构造 QList<QNetworkCookie>类型 cookies的方法，用于构造cookies
 *
 *加一个构造post数据的方法
 *
 *加一个构造get url的方法
*/
                                                            // QVariant 类型设置默认值为空的方法有异常，再查
void httpMethod::sendRequest(const QUrl &url,  const QVariant &cookievar,const QString &method,  const QByteArray &postdata)
{
    //mUrl = url;
    //QVariant var;
    //var.setValue(cookielist);

    QNetworkRequest request;
    request.setUrl(url);


    /*/Here we set the data needed for a post request
        QList<QNetworkCookie> cookies = mManager.cookieJar()->cookiesForUrl(mUrl);
        for(auto it = cookies.begin(); it != cookies.end(); ++it){
            request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(*it));
        }

        QUrl post;
        post.addQueryItem("firstParameter", s);
        post.addQueryItem("secondParameter", "O");
        QByteArray ba;
        ba.remove(0,1); //must remove last &

        //searchReq.setUrl(urlSearch);
        pendingReq.insert(manager.post(searchReq, ba));
*/
    if(cookievar != NULL)
    {
       /*
        for(auto it = cookielist.begin(); it != cookielist.end(); ++it){
            request.setHeader(QNetworkRequest::CookieHeader, var.fromValue(*it));
        }
        */
        request.setHeader(QNetworkRequest::CookieHeader, cookievar);
    }


    if(method == tr("GET"))
    {
        mManager->get(request);
    }
    else if(method == tr("POST"))
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


void httpMethod::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return;
    }

    /*/Here i check if there is a cookie for me in the reply and extract it
    cookies = qvariant_cast<QList<QNetworkCookie>>(reply->header(QNetworkRequest::SetCookieHeader));
    if(cookies.count() != 0)
    {
        //you must tell which cookie goes with which url
        mManager.cookieJar()->setCookiesFromUrl(cookies, mUrl);
    }


    //here you can check for the 302 or whatever other header i need
      QVariant newLoc = reply->header(QNetworkRequest::LocationHeader);
      if(newLoc.isValid()){
          //if it IS a reloc header, get the url it points to
          QUrl url(newLoc.toString());
          _req.setUrl(url);
          _pendingReq.insert(_manager.get(_req));
          return;
      }

      //if you have multiple urls you are waiting for replys
      //you can check which one this one belongs to with
      if(reply->url() == urlSearch){
          //do something
      }
*/
    /*
    cookielist = mManager->cookieJar()->cookiesForUrl(mUrl);

    qDebug() << "COOKIES for---------->" << mUrl.host() << cookielist;

    QNetworkCookie cookie;
    foreach (cookie, cookielist)
    {
        qDebug()<< "---------------------";
        qDebug()<< cookie.name() << "--------------->" << cookie.value();
    }
    */
    //qDebug() << "reply---------->" << reply->readAll();

    this->reply = reply;
    /*/var = reply->header(QNetworkRequest::SetCookieHeader);
    cookielist = qvariant_cast< QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    foreach (cookie, cookielist)
    {
        qDebug()<< "----------11111111111-----------";
        qDebug()<< cookie.name() << "--------------->" << cookie.value();
    }

    */
    //reply->deleteLater();
    qDebug() << this->reply->readAll();
}
/*
QList<QNetworkCookie> httpMethod::getCookieList()
{
    return cookielist;
}
*/
/*
QNetworkReply *httpMethod::getReply()
{
    return reply;
}
*/
