#ifndef COOKIESHANDLER_H
#define COOKIESHANDLER_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkCookie>
#include <QEventLoop>
#include <QDebug>

/**
 *类名：httpMethod
 *作用：提供POST GET 网络操作功能
**/
class httpMethod: public QObject{
    Q_OBJECT

public:
    explicit httpMethod(QObject *parent = 0);
    ~httpMethod();

    static const int GET = 1;   // GET方法
    static const int POST = 2;  // POST方法

    QNetworkReply* sendRequest(const QUrl &url,  const QVariant &cookievar = NULL, const int method = GET, const QByteArray &postdata = NULL);
    QNetworkReply* POSTMethod(const QNetworkRequest &request, const QByteArray &postData);
    QNetworkReply* GETMethod(const QNetworkRequest &request);
private:
    QNetworkAccessManager *mManager;



};


#endif // COOKIESHANDLER_H
