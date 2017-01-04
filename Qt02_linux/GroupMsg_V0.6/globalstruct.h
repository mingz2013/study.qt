#ifndef INIT_H
#define INIT_H

#include <QNetworkCookie>
#include <QString>
#include "myjson.h"


/**
 *全局cookie变量结构体
**/
typedef struct Cookie_Struct{
    // cookie相关变量
    // 第一次要发送的cookie
    QNetworkCookie chkuin;
    // 第一次get获得验证码令牌收到的cookie
    QNetworkCookie confirmuin;
    QNetworkCookie ptvfsession;
    QNetworkCookie ptisp;
    // 第二次get验证码图片获得的cookie
    QNetworkCookie verifysession;
    // getlogin返回的cookie
    QNetworkCookie pt2gguin;
    QNetworkCookie uin;
    QNetworkCookie skey;
    QNetworkCookie RK;
    QNetworkCookie ptcz;
    QNetworkCookie ptwebqq;
    QNetworkCookie superuin;
    QNetworkCookie superkey;
    QNetworkCookie ETK;
    QNetworkCookie ptuserinfo;
    //getcheck_sig需要的
     QNetworkCookie ptui_loginuin;
    // getcheck_sig收到的
    QNetworkCookie p_uin;
    QNetworkCookie p_skey;
    QNetworkCookie pt4_token;
    // postlogin 发送的cookie

} COOKIE;

/**
 *全局string变量结构体
**/
typedef struct String_Struct{
    QString vfwebqq;
    QString QQ_Number;  // QQ号
    QString nick;   // 昵称
    QString clientid;   // 客户端id
    QString psessionid;

}STRING;

typedef struct Other_Struct{
    QJsonObject myselfInfo; // 个人信息
}OTHER;


#endif // INIT_H
