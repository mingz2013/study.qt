#include "mycookiejar.h"

MyCookieJar::MyCookieJar(QObject *parent) :
    QNetworkCookieJar(parent)
{

}


QString MyCookieJar::getCookieValue(QString name)
{

    QList<QNetworkCookie> list = this->allCookies();
    QNetworkCookie Cookie;
    foreach (Cookie, list) {
        if(QString(Cookie.name()) == name)
        {
            return QString(Cookie.value());
        }
    }
    return "";
}



void MyCookieJar::setCookies(const QList<QNetworkCookie>& cookieList)
{

    if(this == NULL)
    {
        return;
    }

    QList<QNetworkCookie> list;
    list.append(this->allCookies());
    list.append(cookieList);

    this->setAllCookies(list);


}
