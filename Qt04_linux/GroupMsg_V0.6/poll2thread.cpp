#include "poll2thread.h"
#include <QDebug>
#include "globalset.h"

extern GlobalSet globalset;// 引用全局变量

poll2Thread::poll2Thread(QWidget *parent) :
    QThread(parent)
{
    httpmethod = new httpMethod(this);
    quit = false;
}

void poll2Thread::run()
{
    while(!quit){
        post_poll2();
        sleep(5);
    }

}

void poll2Thread::stop()
{
    quit = true;
}


void poll2Thread::post_poll2()
{
    // url
    QString str = "http://d.web2.qq.com/channel/poll2";
    //qDebug() << "str----------->" << str;
    QUrl url(str);

    //cookie
    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.ptisp);
    list.append(globalset.cookie_struct.verifysession);
    list.append(globalset.cookie_struct.ptui_loginuin);
    list.append(globalset.cookie_struct.pt2gguin);
    list.append(globalset.cookie_struct.uin);
    list.append(globalset.cookie_struct.skey);
    list.append(globalset.cookie_struct.RK);
    list.append(globalset.cookie_struct.ptcz);
    list.append(globalset.cookie_struct.ptwebqq);
    list.append(globalset.cookie_struct.p_uin);
    list.append(globalset.cookie_struct.p_skey);
    list.append(globalset.cookie_struct.pt4_token);

    //qDebug() << list;
    QVariant var;
    var.setValue(list);
    //qDebug() << "var------>" << var;
    // postdata
    QByteArray postData;
    QString strPost = "r=%7B%22clientid%22%3A%22"+globalset.string_struct.clientid+"%22%2C%22psessionid%22%3A%22"+globalset.string_struct.psessionid+"%22%2C%22key%22%3A0%2C%22ids%22%3A%5B%5D%7D&clientid="+globalset.string_struct.clientid+"&psessionid=" + globalset.string_struct.psessionid;
    postData.append(strPost.toUtf8());
    //qDebug() << "postdata-------------->" << postData;

    // 发送请求
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::CookieHeader, var);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.length());  // 设置数据的长度
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2");
    //qDebug() << "POSTMETHOD";
    QNetworkReply* reply = httpmethod->POSTMethod(request, postData);
    QString context = reply->readAll();
    reply->deleteLater();

    //qDebug() << "context----------->" << context;

    emit poll2Signal(context);
/*
    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;
*/
}
