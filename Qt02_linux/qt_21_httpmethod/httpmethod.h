#ifndef COOKIESHANDLER_H
#define COOKIESHANDLER_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkCookie>
#include <QDebug>


class httpMethod: public QObject{
    Q_OBJECT

public:
    explicit httpMethod(QObject *parent = 0);
    ~httpMethod();

    static const int GET = 1;   // GET方法
    static const int POST = 2;  // POST方法
    QNetworkReply *reply;
    QNetworkAccessManager *mManager;
    void sendRequest(const QUrl &url,  const QVariant &cookievar = NULL, const int method = GET, const QByteArray &postdata = NULL);

private slots:
    void replyFinished(QNetworkReply *reply);

private:



};


#endif // COOKIESHANDLER_H
