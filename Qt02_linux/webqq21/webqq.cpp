#include "webqq.h"
#include "tools.h"



webQQ::webQQ(QObject *parent) :
    QObject(parent)
{
    httpmethod = new httpMethod(this);
    msg_id = 0;
}

/**
 *函数名：getverifycode
 *  返回值：bool 如果需要获取验证码图片，返回true，不许要获取图片，返回false
 *  作用：第一个GET请求，获取文字验证码，判断是否需要验证码验证
**/
bool webQQ::getverifycode()
{
    qDebug() << "in getverifycode()";
    // url
    QString url = "https://ssl.ptlogin2.qq.com/check?uin=" + qqNumber + "&appid=1003903&js_ver=10037&js_type=0&login_sig=a5plBY*dGrO823Rz7isbMqfxGbtHb2CcVcpsjAyXzt-2g6PIgmhXuPq1O71Cesqw&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html&r=0." + Tools::getRand(Tools::getRand(15, 17));// 15 或 16位随机数

    //cookie
    QNetworkCookie chkuin;
    chkuin.setName("chkuin");
    QByteArray byte_QQ;
    byte_QQ.append(qqNumber);
    chkuin.setValue(byte_QQ);
    httpmethod->myCookieJar->insertCookie(chkuin);

    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url);

    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;//ptui_checkVC('0','!WDE','\x00\x00\x00\x00\x12\x37\x24\x51');

    textCode = Tools::getMidOfTwoText(context, tr("','"), tr("','"));
    qDebug() << "textCode--------------->" << textCode;

    pt_uin = context.right(35).left(32);
    qDebug() << "pt_uin----------->" << pt_uin;


    reply->deleteLater();
    hadGetverifycode = true;    // 当前QQ号已获取文字验证码

    // 根据获取的数据判断是否需要验证码
    if(textCode.length() == 4)
    {// 不许要验证码

        return false;
    }else if(textCode.length() > 4)
    {// 需要验证码，获取验证码图片
        return true;
    }else if(textCode.length() == 0)
    {// QQ号有错误
        qDebug() << "textcode长度为0，QQ号有错误，请重新输入";

        return false;
    }else{
        // 未知情况
        qDebug() << "----------textcode长度在非指定范围内，----------";

        return false;
    }

}


/**
 *函数名：getverifyimg
 *  返回值：void
 *  作用：获取并显示验证码图片
**/
QImage webQQ::getverifyimg()
{
    qDebug() << "getverifyimg";
    // url
    QString url = "https://ssl.captcha.qq.com/getimage?aid=1003903&r=0." + Tools::getRand(17) + "&uin=" + qqNumber;



    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url);

    // 获取数据
    QImageReader imageReader(reply);

    QImage image = imageReader.read();
    reply->deleteLater();
    return image;





}



bool webQQ::Login()
{
    bool b = getlogin();
    if(b == false)
    {
        // 登录失败
        return false;
    }
    qDebug() << "getcheck_sig begin----------+++++++-------------------->";
    getcheck_sig();
    qDebug() << "postlogin--------------------------------------------";
    postlogin();
    return true;
}
/**
 *函数名：getlogin
 *  返回值：bool
 *  作用：第一个login
**/
bool webQQ::getlogin()
{

    QString verifycode;
    if(textCode.length() == 4)
    {
        verifycode = textCode;
    }else{
        verifycode = textCode_write;
    }



    qDebug() << "verifycode------------>" << verifycode;
    qDebug() << "pt_uin---------------->" << pt_uin;
    //runJS(".//QQ.js", "ahzosdks2342", "!ADS", "\x00\x00\x00\x00\x12\x37\x24\x51");
    qDebug() << "passwd.data---->" << passwd.toLatin1().data();

    QString md5_passwd = DoMD5(passwd.toLatin1().data(), verifycode.toLatin1().data(), pt_uin.toLatin1().data());
    qDebug() << "md5_passwd----------------->" << md5_passwd;
    // url
    QString url = "https://ssl.ptlogin2.qq.com/login?u=" + qqNumber + "&p=" + md5_passwd + "&verifycode=" + verifycode + "&webqq_type=10&remember_uin=1&login2qq=1&aid=1003903&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=1-11-11722&mibao_css=m_webqq&t=1&g=1&js_type=0&js_ver=10038&login_sig=FHtWnWD4qzo7PYp*3mDJtPxsYzwUAp9SFO0HlDBzsV5iDmqoldIny4NSmA3NRTwj";


    QNetworkReply* reply = httpmethod->GETMethod(url);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;
    //...n_hour%3D0%26regmaster%3D0','0','登录成功！', '明子');
    //ptuiCB('3','0','','0','您输入的帐号或密码不正确，请重新输入。', 'xxx');
    int i = context.lastIndexOf("登录成功！");
    if(i == -1)
    {
        qDebug() << "登录失败";

        return false;
    }
    nick = Tools::getMidOfTwoText(context, tr("'登录成功！', '"), tr("');"));
    qDebug() << "nick---------->" << nick;


    //ptsig = Tools::getMidOfTwoText(context, tr("ptsig%3D"), tr("%26s_url"));
    //qDebug() << "ptsig--------------------->" << ptsig;
    getcheck_sig_url = Tools::getMidOfTwoText(context, tr("ptuiCB('0','0','"), tr("','0','登录成功！'"));
    //qDebug() << "getpt4_302_url------------>" << getcheck_sig_url;
    //getcheck_sig_url = Tools::getMidOfTwoText(context, tr("pt4_302?u1="), tr("','0','登录成功！"));
    qDebug() << "getcheck_sig_url---------->" << getcheck_sig_url;


    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    reply->deleteLater();
    qDebug() << "COOKIES for---------->" << cookielist;
    httpmethod->myCookieJar->setCookies(cookielist);

    return true;

}

/**
 *函数名：getcheck_sig
 *作用：get方法
**/
void webQQ::getcheck_sig()
{
    // url
    //QString str = "http://ptlogin4.web2.qq.com/check_sig?pttype=1&uin=xxx&service=login&nodirect=0&ptsig="+ptsig+"&s_url=http%3a%2f%2fweb2.qq.com%2floginproxy.html%3flogin2qq%3d1%26webqq%5ftype%3d10&f_url=&ptlang=2052&ptredirect=100&aid=1003903&daid=164&j_later=0&low_login_hour=0&regmaster=0";
    QString url = getcheck_sig_url;
    QNetworkCookie ptui_loginuin;
    ptui_loginuin.setName("ptui_loginuin");
    QByteArray byte_QQ;
    byte_QQ.append(qqNumber);
    ptui_loginuin.setValue(byte_QQ);
    httpmethod->myCookieJar->insertCookie(ptui_loginuin);
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;

    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    httpmethod->myCookieJar->setCookies(cookielist);


    reply->deleteLater();
}


/**
 *函数名：postlogin
 *  返回值：void
 *  作用：第二个login，使其它用户得知自己上线信息
**/
void webQQ::postlogin()
{
    // url
    QString url = "http://d.web2.qq.com/channel/login2";


    // postdata
    QByteArray postData;
    //QString status = "online";// 这里要控制一下
    clientid = Tools::getRand(Tools::getRand(7, 9));

    QString strPost = "r=%7B%22status%22%3A%22online%22%2C%22ptwebqq%22%3A%22" + httpmethod->myCookieJar->getCookieValue("ptwebqq") + "%22%2C%22passwd_sig%22%3A%22%22%2C%22clientid%22%3A%22" + clientid + "%22%2C%22psessionid%22%3Anull%7D&clientid=" + clientid + "&psessionid=null";
    postData.append(strPost.toUtf8());

    qDebug() << "postdata-------------->" << postData;
    // 发送请求

    QString referer = "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2";

    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;
    psessionid = obj.value("result").toObject().value("psessionid").toString();
    qDebug() << "psessionid---------->" << psessionid;
    vfwebqq = obj.value("result").toObject().value("vfwebqq").toString();
    qDebug() << "vfwebqq------------->" << vfwebqq;



}

/**
 *获取个性签名
**/
void webQQ::get_single_long_nick2()
{
    // url
    QString url = "http://s.web2.qq.com/api/get_single_long_nick2?tuin=" + qqNumber + "&vfwebqq=" + vfwebqq + "&t=" + Tools::getCurrentTimeStamp();

    QString referer = "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3";
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url, referer);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;
    lnick = obj.value("result").toArray().first().toObject().value("lnick").toString();
    qDebug() << "lnick---------->" << lnick;

    emit lninkSignal(lnick);

}

/**
 *获取好友列表
**/
void webQQ::post_get_user_friends2()
{
    // url
    QString url = "http://s.web2.qq.com/api/get_user_friends2";


    // postdata
    QByteArray postData;

    QString hash = DoHash(qqNumber.toLatin1().data() , httpmethod->myCookieJar->getCookieValue("ptwebqq").toLatin1().data());

    qDebug() << "hash------------>" << hash;
    QString strPost = "r=%7B%22h%22%3A%22hello%22%2C%22hash%22%3A%22" + hash + "%22%2C%22vfwebqq%22%3A%22" + vfwebqq + "%22%7D";
    postData.append(strPost.toUtf8());
    qDebug() << "postdata-------------->" << postData;


    QString referer = "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3";

    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;
    qDebug() << obj.value("retcode");
    if(obj.value("retcode").toBool() != false){qDebug() << "获取好友列表失败";return;}

    QJsonObject friends_result = obj.value("result").toObject();

    emit friends_result_Signal(friends_result);





}


/**
 *获取群列表
**/
void webQQ::post_get_group_name_list_mask2()
{
    // url
    QString url = "http://s.web2.qq.com/api/get_group_name_list_mask2";



    // postdata
    QByteArray postData;
    QString strPost = "r=%7B%22vfwebqq%22%3A%22" + vfwebqq + "%22%7D";
    postData.append(strPost.toUtf8());
    qDebug() << "postdata-------------->" << postData;


    QString referer = "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3";
    qDebug() << "POSTMETHOD";
    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;

    QJsonObject qun_result = obj.value("result").toObject();

    emit qun_result_Signal(qun_result);


}

/**
 *获取在线好友列表
**/
void webQQ::get_online_buddies2()
{
    // url
    QString url = "http://d.web2.qq.com/channel/get_online_buddies2?clientid=" + clientid + "&psessionid=" + psessionid + "&t=" + Tools::getCurrentTimeStamp();



    QString referer = "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2";
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url, referer);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << "obj------------------->" << obj;
    qDebug() << "obj.value(\"retcode\")---->" << obj.value("retcode");
    if(obj.value("retcode").toBool() != false) {qDebug() << "get online buddylist wrong"; return;}
    qDebug() << "retcode:0";
    QJsonArray onlineList = obj.value("result").toArray();

    emit onlinelist_Signal(onlineList);

}

/**
 *获取个人信息
**/
void webQQ::get_friend_info2()
{
    // url
    QString url = "http://s.web2.qq.com/api/get_friend_info2?tuin="+qqNumber+"&verifysession=&code=&vfwebqq="+vfwebqq+"&t=" + Tools::getCurrentTimeStamp();

    QString referer = "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3";
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url, referer);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;

    if(obj.value("retcode").toBool() != false) {qDebug() << "get self info wrong"; return;}

    myselfInfo = obj.value("result").toObject();
    qDebug() << "myselfInfo---------->" << myselfInfo;

}

void webQQ::post_poll2()
{
    // url
    QString url = "http://d.web2.qq.com/channel/poll2";


    // postdata
    QByteArray postData;
    QString strPost = "r=%7B%22clientid%22%3A%22"+clientid+"%22%2C%22psessionid%22%3A%22"+psessionid+"%22%2C%22key%22%3A0%2C%22ids%22%3A%5B%5D%7D&clientid="+clientid+"&psessionid=" + psessionid;
    postData.append(strPost.toUtf8());
    //qDebug() << "postdata-------------->" << postData;


    QString referer = "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2";

    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;

    emit poll2_obj_Signal(obj);
}



/**
 *获取群信息和群成员列表
**/
void webQQ::get_group_info_ext2(QString code)
{



    qDebug() << "code---->" << code;
    // url
    QString url = "http://s.web2.qq.com/api/get_group_info_ext2?gcode=" + code + "&cb=undefined&vfwebqq=" + vfwebqq + "&t=" + Tools::getCurrentTimeStamp();



    QString referer = "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3";
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(url, referer);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << "obj------------------->" << obj;

    if(obj.value("retcode").toBool() != false) {qDebug() << "get qun info wrong"; return;}

    emit group_info_Signal(obj);

}


/**
 *给好友发送消息
**/
void webQQ::post_send_buddy_msg2(QString uin, QString Msg)
{
    // url
    QString url = "http://d.web2.qq.com/channel/send_buddy_msg2";
                 //http://d.web2.qq.com/channel/send_buddy_msg2

    // postdata
    QByteArray postData;


    qDebug() << "uin--------->" << uin;
    QString face = QString::number(myselfInfo.value("face").toDouble());
    qDebug() << "face------>" << face;
    QString strPost = "r=%7B%22to%22%3A"+uin+"%2C%22face%22%3A"+face+"%2C%22content%22%3A%22%5B%5C%22"+Msg+"%5C%22%2C%5C%22%5C%5Cn%E3%80%90%E6%8F%90%E7%A4%BA%EF%BC%9A%E6%AD%A4%E7%94%A8%E6%88%B7%E6%AD%A3%E5%9C%A8%E4%BD%BF%E7%94%A8Q%2B%20Web%EF%BC%9Ahttp%3A%2F%2Fweb2.qq.com%2F%E3%80%91%5C%22%2C%5B%5C%22font%5C%22%2C%7B%5C%22name%5C%22%3A%5C%22%E5%AE%8B%E4%BD%93%5C%22%2C%5C%22size%5C%22%3A%5C%2210%5C%22%2C%5C%22style%5C%22%3A%5B0%2C0%2C0%5D%2C%5C%22color%5C%22%3A%5C%22000000%5C%22%7D%5D%5D%22%2C%22msg_id%22%3A"+QString::number(msg_id)+"%2C%22clientid%22%3A%22"+clientid+"%22%2C%22psessionid%22%3A%22"+psessionid+"%22%7D&clientid="+clientid+"&psessionid=" + psessionid;
    msg_id++;
    postData.append(strPost.toUtf8());
    qDebug() << "postdata-------------->" << postData;


    QString referer = "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2";
    qDebug() << "POSTMETHOD";
    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << "obj------------------->" << obj;

}

/**
 *发送群消息
**/
void webQQ::post_send_qun_msg2(QString group_uin, QString Msg)
{
    // url
    QString url = "http://d.web2.qq.com/channel/send_qun_msg2";

    // postdata
    QByteArray postData;

    qDebug() << "group_uin-->" << group_uin;
    QString strPost = "r=%7B%22group_uin%22%3A"+group_uin+"%2C%22content%22%3A%22%5B%5C%22"+Msg+"%5C%22%2C%5C%22%5C%5Cn%E3%80%90%E6%8F%90%E7%A4%BA%EF%BC%9A%E6%AD%A4%E7%94%A8%E6%88%B7%E6%AD%A3%E5%9C%A8%E4%BD%BF%E7%94%A8Q%2B%20Web%EF%BC%9Ahttp%3A%2F%2Fweb2.qq.com%2F%E3%80%91%5C%22%2C%5B%5C%22font%5C%22%2C%7B%5C%22name%5C%22%3A%5C%22%E5%AE%8B%E4%BD%93%5C%22%2C%5C%22size%5C%22%3A%5C%2210%5C%22%2C%5C%22style%5C%22%3A%5B0%2C0%2C0%5D%2C%5C%22color%5C%22%3A%5C%22000000%5C%22%7D%5D%5D%22%2C%22msg_id%22%3A"+QString::number(msg_id)+"%2C%22clientid%22%3A%22"+clientid+"%22%2C%22psessionid%22%3A%22"+psessionid+"%22%7D&clientid="+clientid+"&psessionid=" + psessionid;
    msg_id++;
    postData.append(strPost.toUtf8());
    qDebug() << "postdata-------------->" << postData;


    QString referer= "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2";
    QNetworkReply* reply = httpmethod->POSTMethod(url, postData, referer);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << "obj------------------->" << obj;

}

QString webQQ::DoMD5(QString password, QString verifycode, QString pt_uin)
{
    QScriptValueList _args;
    _args << QScriptValue(password) << QScriptValue(verifycode) << QScriptValue(pt_uin);
    return runJS("JS/QQ.js", "func", _args);
}
QString webQQ::DoHash(QString QQNumber, QString ptwebqq)
{
    QScriptValueList _args;
    _args << QScriptValue(QQNumber) << QScriptValue(ptwebqq);
    return runJS("JS/hash.js", "hash", _args);

}
QString webQQ::runJS(QString scriptfile, QString functionname, QScriptValueList _args)
{
    QString m_encodePassword = "";
    QFile _scriptFile(scriptfile);
    if (!_scriptFile.open(QIODevice::ReadOnly))
    {
        m_encodePassword.clear();
        qWarning() << "encodePass.js open failed";
        return NULL;
     }
    QTextStream _stream(&_scriptFile);
    QString _contents = _stream.readAll();
    _scriptFile.close();
    QScriptEngine _engine;
    QScriptValue _js = _engine.evaluate(_contents);
    QScriptValue _passwordEncoding = _engine.globalObject().property(functionname);

    m_encodePassword = _passwordEncoding.call(QScriptValue(), _args).toString();
    return m_encodePassword;

}

