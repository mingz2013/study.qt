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

    void sendRequest(const QUrl &url,  const QVariant &cookievar = NULL, const QString &method = tr("GET"), const QByteArray &postdata = NULL);

   // QList<QNetworkCookie> getCookieList();
    //QNetworkReply * getReply();

    QNetworkReply *reply;

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *mManager;
    //QUrl mUrl;
    //QList<QNetworkCookie>  cookielist;
    //QVariant var;
    //QNetworkReply *reply;
};


#endif // COOKIESHANDLER_H
