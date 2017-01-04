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


class httpMethod: public QObject{
    Q_OBJECT

public:
    explicit httpMethod(QObject *parent = 0);
    ~httpMethod();

    static const int GET = 1;   // GET方法
    static const int POST = 2;  // POST方法

    QNetworkReply* sendRequest(const QUrl &url,  const QVariant &cookievar = NULL, const int method = GET, const QByteArray &postdata = NULL);

private:
    QNetworkAccessManager *mManager;



};


#endif // COOKIESHANDLER_H
