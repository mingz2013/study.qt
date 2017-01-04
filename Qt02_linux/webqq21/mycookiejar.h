#ifndef MYCOOKIEJAR_H
#define MYCOOKIEJAR_H

#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>

class MyCookieJar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit MyCookieJar(QObject *parent = 0);

    QString getCookieValue(QString name);

    void setCookies(const QList<QNetworkCookie>& cookieList);
    
};

#endif // MYCOOKIEJAR_H
