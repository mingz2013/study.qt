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
#include "mycookiejar.h"
#include <QNetworkProxy>

/**
 *类名：httpMethod
 *作用：提供POST GET 网络操作功能
**/
class httpMethod: public QObject{
    Q_OBJECT

public:
    explicit httpMethod(QObject *parent = 0);
    ~httpMethod();

    MyCookieJar *myCookieJar;

    QNetworkReply* POSTMethod(const QString url, const QByteArray &postData, const QString referer = "");
    QNetworkReply* GETMethod(const QString url, const QString referer = "");
    void setProxy(QString hostname, int port, QString proxyUser, QString proxyPassword);

private:
    QNetworkAccessManager *mManager;

};


#endif // COOKIESHANDLER_H
