#ifndef WEBQQ_H
#define WEBQQ_H

#include <QObject>
#include <QString>
#include "httpmethod.h"
#include <QImageReader>
#include "myjson.h"
#include <QScriptValue>
#include <QScriptEngine>
#include <QScriptValueList>

class webQQ : public QObject
{
    Q_OBJECT
public:
    QString qqNumber;
    QString passwd;
    bool hadGetverifycode;
    QString textCode;
    QString textCode_write;
    QString nick;
    QString lnick;
    QJsonObject myselfInfo;

    explicit webQQ(QObject *parent = 0);

    bool getverifycode();
    QImage getverifyimg();
    bool Login();
    void post_poll2();
    void get_single_long_nick2();
    void post_get_user_friends2();
    void post_get_group_name_list_mask2();
    void get_online_buddies2();
    void get_friend_info2();

    void get_group_info_ext2(QString code);
    void post_send_buddy_msg2(QString uin, QString Msg);
    void post_send_qun_msg2(QString group_uin, QString Msg);

private:
    httpMethod *httpmethod;


    QString pt_uin;

    QString getcheck_sig_url;
    QString clientid;
    QString vfwebqq;
    QString psessionid;

    int msg_id;


    bool getlogin();
    void getcheck_sig();
    void postlogin();

    QString DoMD5(QString password, QString verifycode, QString pt_uin);
    QString DoHash(QString QQNumber, QString ptwebqq);
    QString runJS(QString scriptfile, QString functionname, QScriptValueList _args);
signals:
    void poll2_obj_Signal(QJsonObject obj);
    void lninkSignal(QString lnick);
    void friends_result_Signal(QJsonObject friends_result);
    void qun_result_Signal(QJsonObject qun_result);
    void onlinelist_Signal(QJsonArray onlineList);
    void group_info_Signal(QJsonObject obj);

};

#endif // WEBQQ_H
