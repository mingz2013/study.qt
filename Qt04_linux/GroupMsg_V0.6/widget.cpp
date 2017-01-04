#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QImageReader>
#include "v8_js.h"
#include <string.h>
#include "globalset.h"
#include <QDir>
#include <QSettings>

Q_DECLARE_METATYPE(QJsonObject)// 声明类型,以便var.setvalue()

extern GlobalSet globalset;// 引用全局变量

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init(); // 初始化
}

Widget::~Widget()
{
    delete ui;
}

/**
 *方法名：init
 *  参数：无
 *  返回值：无
 *  作用：程序初始化
**/
void Widget::Init()
{   // 初始化
    need_verifycode(false); // 初始设置为不需要验证码
    globalset.string_struct.QQ_Number.clear();   // QQ_Numner变量初始化为空
    httpmethod = new httpMethod(this);  // http操作类
    hadGetverifycode = false;   // 初始化 当前QQ号未获取过文字验证码
    textCode_write.clear();  // 输入的验证码
    textCode.clear();        // 得到的文字验证码
    pt_uin.clear();

    poll2thread = new poll2Thread(this);
    QObject::connect(poll2thread, SIGNAL(poll2Signal(QString)), this, SLOT(poll2ThreadSlots(QString)));
    connect(this, SIGNAL(group_message_Signal(QJsonObject)), this, SLOT(group_message_Slot(QJsonObject)));

    set_Log(QString("读取配置文件...."));
    QFile file("Config.ini");
    if(file.exists()){
        readSettings();
    }else{
        set_Log(QString("配置文件不存在"));
    }

    length_low = ui->spinBox_low->text().toInt();
    length_high = ui->spinBox_high->text().toInt();
    key_list = ui->textEdit_keys->toPlainText().split(",");
    hackword_list = ui->textEdit_hackwords->toPlainText().split(",");
    repleaseword_list = ui->textEdit_replease->toPlainText().split(",");
    replease_word = ui->lineEdit_replease_word->text();
    tel_list = ui->textEdit_tel->toPlainText().split(",");



    set_showText(QString("程序初始化完毕"));

}

/**
 *方法名：need_verifycode
 *  参数1：bool类型
 *  返回值：void
 *  作用：显示或隐藏 验证码系列控件
**/
void Widget::need_verifycode(bool need)
{   // 验证码系列控件的变化
    if(need == true)
    {
        ui->label_verifycode->setEnabled(true);
        ui->lineEdit_verifycode->setEnabled(true);
        //ui->label_verifycode1->setHidden(true);
        ui->label_changeimg_link->setEnabled(true);
        ui->label_imgverify->setEnabled(true);

    }
    else
    {
        ui->label_verifycode->setEnabled(false);
        ui->lineEdit_verifycode->setEnabled(false);
        //ui->label_verifycode1->setHidden(false);
        ui->label_changeimg_link->setEnabled(false);
        ui->label_imgverify->setEnabled(false);
    }
}

/**
 *方法名：set_showText
 *  参数1：Qstring类型
 *  作用：界面上label_show控件添加提示文本
**/
void Widget::set_showText(QString text)
{
    set_Log(text);
    text = "<html><head/><body><p align=\"center\"><span style=\" color:#ff0000;\">" + text + "</span></p></body></html>";
    ui->label_show->setText(text);

}

/**
 *日志记录
**/
void Widget::set_Log(QString text)
{
    // 日志兰加上记录
    //将记录写入文本保存
    text = Tools::getTimeNow() + " " + text ;
    ui->plainTextEdit_Log->appendPlainText(text);

}

/**
 *登录按钮单击槽函数
**/
void Widget::on_pushButton_login_clicked()
{
    if(NULL != ui->lineEdit_QQNumber->text())
    {
        bool allright = true;
        if(NULL != ui->lineEdit_password->text())
        {
            qDebug() << "密码框不为空,go on";
        }else{
            set_showText(tr("密码输入为空，请输入密码"));
            allright = false;
        }

        if(globalset.string_struct.QQ_Number == ui->lineEdit_QQNumber->text() && hadGetverifycode == true)
        { // 已经获取了文字验证码，
            qDebug() << "had get code";
        }else{
            // 还未获取文字验证码
            globalset.string_struct.QQ_Number = ui->lineEdit_QQNumber->text();
            qDebug() << "there need a GET method";
            bool need_img = getverifycode();
            if(need_img)
            {
                allright = false;   // 需要验证码，需要暂停，等待输入验证码
                qDebug() << "需要输入验证码";
            }else{
                qDebug() << "不许要输入验证码";
            }
        }

        if(true == allright)
        {
            // allright,do something continue need
            qDebug() << "allright";
            if(textCode.length() > 4)
            {// 需要验证码
                if(ui->lineEdit_verifycode->text() == NULL)
                {// 验证码为空
                    set_showText(tr("请输入验证码"));
                    return;
                }else{
                    // 得到输入的验证码
                    textCode_write = ui->lineEdit_verifycode->text();
                }
            }

            qDebug() << "need a post method";
            bool b = getlogin();
            if(b == false)
            {
                // 登录失败
                return;
            }
            qDebug() << "getpt4_302-----------------------------";
            //getpt4_302();
            qDebug() << "getcheck_sig begin----------+++++++-------------------->";
            getcheck_sig();
            qDebug() << "postlogin--------------------------------------------";
            postlogin();

            loginhide();// 隐藏登录控件
            // 登录成功后获取群列表，开始线程poll2
            post_get_group_name_list_mask2();// 获取群列表
            poll2thread->start();



            set_showText(QString("登录成功！当前QQ号：") + globalset.string_struct.QQ_Number + QString("  昵称：") + globalset.string_struct.nick);

        }else{
            return;
        }
    }else{
        set_showText(tr("QQ号输入为空或者错误，请重新输入"));
    }

}

/**
 *登录控件隐藏
**/
void Widget::loginhide()
{
    ui->label_QQ->hide();
    ui->lineEdit_QQNumber->hide();
    ui->label_pwd->hide();
    ui->lineEdit_password->hide();
    ui->label_verifycode->hide();
    ui->lineEdit_verifycode->hide();
    ui->label_imgverify->hide();
    ui->label_changeimg_link->hide();
    ui->pushButton_login->hide();
}

/**
 *imgverify label 被单击
**/
void Widget::on_label_imgverify_Clicked(verifyLabel *)
{
    getverifyimg();
    set_Log(QString("刷新验证码"));
}

/**
 *changeimg label 被单击
**/
void Widget::on_label_changeimg_link_Clicked(verifyLabel *)
{
    getverifyimg();
    set_Log(QString("刷新验证码"));
}

/**
 *密码框获取焦点
**/
void Widget::on_lineEdit_password_focusInSignal()
{
    if(ui->lineEdit_QQNumber->text() != NULL)   // 输入的不为空，并且是正确的qq号,这里用正则表达式判断,都是数字，且长度限制，开头不能为0
    {
        if(globalset.string_struct.QQ_Number.isEmpty())
        {
            qDebug() << "QQ_Number is empty";
            goto change;
        }else{
            if(globalset.string_struct.QQ_Number != ui->lineEdit_QQNumber->text())
            {
                qDebug() << "号码变化了，重新赋值，并get";
                goto change;
            }else{
                // do nothing
                return;
            }
        }
    }else{
        // QQ号输入为空,或者输入不争却，提示用户重新输入
        qDebug() << "QQ号输入空，请重新输入";
        //set_showText(tr("QQ号输入为空或者输入错误，请重新输入"));
        return;
    }
change:
    hadGetverifycode = false;   // 当前号码已改变
    globalset.string_struct.QQ_Number = ui->lineEdit_QQNumber->text();
    qDebug() << "QQ_Number----------->" + globalset.string_struct.QQ_Number;
    qDebug() << "focusIn, there will have a GET method";
    bool need_img = getverifycode();
    if(need_img)
    {
        qDebug() << "需要输入验证码";
        set_Log(QString("需要验证码"));
    }else{
        qDebug() << "不许要输入验证码";
        set_Log(QString("不需要验证码"));
    }
}

/**
 *qqnumber输入框失去焦点
**/
void Widget::on_lineEdit_QQNumber_focusOutSignal()
{
    // ui->lineEdit_QQNumber->text() 去首尾空 再付给自己
    qDebug() << tr("这里要 对输入的内容 去首尾空 然后再付给自己");
    ui->lineEdit_QQNumber->setText(ui->lineEdit_QQNumber->text().trimmed());
}

/**
 *函数名：getverifycode
 *  返回值：bool 如果需要获取验证码图片，返回true，不许要获取图片，返回false
 *  作用：第一个GET请求，获取文字验证码，判断是否需要验证码验证
**/
bool Widget::getverifycode()
{
    qDebug() << "in getverifycode()";
    // url
    QString str = "https://ssl.ptlogin2.qq.com/check?uin=" + globalset.string_struct.QQ_Number + "&appid=1003903&js_ver=10037&js_type=0&login_sig=a5plBY*dGrO823Rz7isbMqfxGbtHb2CcVcpsjAyXzt-2g6PIgmhXuPq1O71Cesqw&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html&r=0." + Tools::getRand(Tools::getRand(15, 17));// 15 或 16位随机数
    qDebug() << str;
    QUrl url(str);
    //cookie
    globalset.cookie_struct.chkuin.setName("chkuin");
    QByteArray byte_QQ;
    byte_QQ.append(globalset.string_struct.QQ_Number);
    globalset.cookie_struct.chkuin.setValue(byte_QQ);

    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.chkuin);
    QVariant var;
    var.setValue(list);
    // 发送请求
    QNetworkReply* reply = httpmethod->sendRequest(url, var);

    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;//ptui_checkVC('0','!WDE','\x00\x00\x00\x00\x12\x37\x24\x51');

    textCode = Tools::getMidOfTwoText(context, tr("','"), tr("','"));
    qDebug() << "textCode--------------->" << textCode;

    pt_uin = context.right(35).left(32);
    qDebug() << "pt_uin----------->" << pt_uin;

    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    qDebug() << "COOKIES for---------->" << cookielist;

    QNetworkCookie cookie_set;
    foreach (cookie_set, cookielist)
    {

        qDebug()<< "---------------------";
        qDebug()<< cookie_set.name() << "--------------->" << cookie_set.value();
        if(QString(cookie_set.name()) == tr("confirmuin"))
        {
            globalset.cookie_struct.confirmuin = cookie_set;
            //qDebug() << confirmuin;
        }else if(QString(cookie_set.name()) == tr("ptvfsession"))
        {
            globalset.cookie_struct.ptvfsession = cookie_set;
            //qDebug() << ptvfsession;
        }else if(QString(cookie_set.name()) == tr("ptisp"))
        {
            globalset.cookie_struct.ptisp = cookie_set;
            //qDebug() << ptisp;
        }
    }
    reply->deleteLater();
    hadGetverifycode = true;    // 当前QQ号已获取文字验证码

    // 根据获取的数据判断是否需要验证码
    if(textCode.length() == 4)
    {// 不许要验证码
        need_verifycode(false);// 界面改变
        return false;
    }else if(textCode.length() > 4)
    {// 需要验证码，获取验证码图片
        qDebug() << "这里获取验证码图片，并显示";
        // 获取验证码图片-并显示------------------写一个方法-----------------***++++++++++++？？？？？？？？？---------------****
        getverifyimg(); // 获取验证码图片并显示
        need_verifycode(true);// 界面改变

        return true;
    }else if(textCode.length() == 0)
    {// QQ号有错误
        qDebug() << "textcode长度为0，QQ号有错误，请重新输入";
        need_verifycode(false);// 界面改变
        return false;
    }else{
        // 未知情况
        qDebug() << "----------textcode长度在非指定范围内，----------";
        need_verifycode(false);// 界面改变
        return false;
    }
}

/**
 *函数名：getverifyimg
 *  返回值：void
 *  作用：获取并显示验证码图片
**/
void Widget::getverifyimg()
{
    // url
    QString str = "https://ssl.captcha.qq.com/getimage?aid=1003903&r=0." + Tools::getRand(17) + "&uin=" + globalset.string_struct.QQ_Number;
    qDebug() << str;
    QUrl url(str);
    //cookie
    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.ptisp); // 获取文字验证码时得到的cookie
    QVariant var;
    var.setValue(list);
    // 发送请求
    QNetworkReply* reply = httpmethod->sendRequest(url, var);

    // 获取数据
    QImageReader imageReader(reply);
    QImage image = imageReader.read();
    if (!image.isNull())
    {
        image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
    }
    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    qDebug() << "COOKIES for---------->" << cookielist;

    QNetworkCookie cookie_set;
    foreach (cookie_set, cookielist)
    {
        qDebug()<< "---------------------";
        qDebug()<< cookie_set.name() << "--------------->" << cookie_set.value();
        if(QString(cookie_set.name()) == tr("verifysession"))
        {
            globalset.cookie_struct.verifysession = cookie_set;
            //qDebug() << verifysession;
        }
    }
    reply->deleteLater();


}

/**
 *函数名：getlogin
 *  返回值：bool
 *  作用：第一个login
**/
bool Widget::getlogin()
{

    QString verifycode;
    if(textCode.length() == 4)
    {
        verifycode = textCode;
    }else{
        verifycode = textCode_write;
    }

    QString passwd = ui->lineEdit_password->text();

    V8_JS *v8js = new V8_JS(this);
    qDebug() << "passwd---------------->" << passwd;
    qDebug() << "verifycode------------>" << verifycode;
    qDebug() << "pt_uin---------------->" << pt_uin;
    //runJS(".//QQ.js", "ahzosdks2342", "!ADS", "\x00\x00\x00\x00\x12\x37\x24\x51");
    qDebug() << "passwd.data---->" << passwd.toLatin1().data();

    //char* argv[argc];
    //argv[0] = passwd.toLatin1().data();
    //argv[1] = verifycode.toLatin1().data();
    //argv[2] = pt_uin.toLatin1().data();
    //passwd.toStdString();
    int argc = 3;
    const string argv[] = {passwd.toLatin1().data(), verifycode.toLatin1().data(), pt_uin.toLatin1().data()};

    QString md5_passwd = v8js->runJS("./JS/QQ.js", "func", argc, argv);
    qDebug() << "md5_passwd----------------->" << md5_passwd;
    // url
    QString str = "https://ssl.ptlogin2.qq.com/login?u=" + globalset.string_struct.QQ_Number + "&p=" + md5_passwd + "&verifycode=" + verifycode + "&webqq_type=10&remember_uin=1&login2qq=1&aid=1003903&u1=http%3A%2F%2Fweb2.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=1-11-11722&mibao_css=m_webqq&t=1&g=1&js_type=0&js_ver=10038&login_sig=FHtWnWD4qzo7PYp*3mDJtPxsYzwUAp9SFO0HlDBzsV5iDmqoldIny4NSmA3NRTwj";
    qDebug() << str;
    QUrl url(str);
    //cookie
    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.chkuin);
    list.append(globalset.cookie_struct.confirmuin);
    list.append(globalset.cookie_struct.ptisp);
    list.append(globalset.cookie_struct.verifysession);
    list.append(globalset.cookie_struct.ptvfsession);
    QVariant var;
    var.setValue(list);
    // 发送请求
    QNetworkReply* reply = httpmethod->sendRequest(url, var);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;
    //...n_hour%3D0%26regmaster%3D0','0','登录成功！', '明子');
    //ptuiCB('3','0','','0','您输入的帐号或密码不正确，请重新输入。', 'xxx');
    int i = context.lastIndexOf("登录成功！");
    if(i == -1)
    {
        qDebug() << "登录失败";
        set_showText(tr("您输入的帐号或密码不正确，请重新输入。"));
        return false;
    }
    globalset.string_struct.nick = Tools::getMidOfTwoText(context, tr("'登录成功！', '"), tr("');"));
    qDebug() << "nick---------->" << globalset.string_struct.nick;


    //ptsig = Tools::getMidOfTwoText(context, tr("ptsig%3D"), tr("%26s_url"));
    //qDebug() << "ptsig--------------------->" << ptsig;
    getcheck_sig_url = Tools::getMidOfTwoText(context, tr("ptuiCB('0','0','"), tr("','0','登录成功！"));
    //qDebug() << "getpt4_302_url------------>" << getpt4_302_url;
    //getcheck_sig_url = Tools::getMidOfTwoText(context, tr("pt4_302?u1="), tr("','0','登录成功！"));
    qDebug() << "getcheck_sig_url---------->" << getcheck_sig_url;


    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    reply->deleteLater();
    qDebug() << "COOKIES for---------->" << cookielist;

    QNetworkCookie cookie_set;
    foreach (cookie_set, cookielist)
    {
        qDebug()<< "---------------------";
        qDebug()<< cookie_set.name() << "--------------->" << cookie_set.value();
        if(QString(cookie_set.name()) == tr("pt2gguin"))
        {
            globalset.cookie_struct.pt2gguin = cookie_set;
            //qDebug() << pt2gguin;
        }else if(QString(cookie_set.name()) == tr("uin"))
        {
            globalset.cookie_struct.uin = cookie_set;
            //qDebug() << uin;
        }else if(QString(cookie_set.name()) == tr("skey"))
        {
            globalset.cookie_struct.skey = cookie_set;
            //qDebug() << skey;
        }else if(QString(cookie_set.name()) == tr("RK"))
        {
            globalset.cookie_struct.RK = cookie_set;
            //qDebug() << RK;
        }else if(QString(cookie_set.name()) == tr("ptcz"))
        {
            if(!cookie_set.value().isEmpty())
            {
                globalset.cookie_struct.ptcz = cookie_set;
                //qDebug() << ptcz;
            }
        }else if(QString(cookie_set.name()) == tr("ptwebqq"))
        {
            globalset.cookie_struct.ptwebqq = cookie_set;
            //qDebug() << ptwebqq;
        }else if(QString(cookie_set.name()) == tr("superuin"))
        {
            globalset.cookie_struct.superuin = cookie_set;
            //qDebug() << superuin;
        }else if(QString(cookie_set.name()) == tr("superkey"))
        {
            globalset.cookie_struct.superkey = cookie_set;
            //qDebug() << superkey;
        }else if(QString(cookie_set.name()) == tr("ETK"))
        {
            globalset.cookie_struct.ETK = cookie_set;
            //qDebug() << ETK;
        }else if(QString(cookie_set.name()) == tr("ptuserinfo"))
        {
            globalset.cookie_struct.ptuserinfo = cookie_set;
            //qDebug() << ptuserinfo;
        }
    }

    return true;

}

/**
 *函数名：getpt4_302
 *作用：get方法
**/
/*
void Widget::getpt4_302()
{
    // url
    QString str = getpt4_302_url;
    qDebug() << str;
    QUrl url(str);
    //cookie
    QList<QNetworkCookie> list;

    list.append(globalset.cookie_struct.confirmuin);
    list.append(globalset.cookie_struct.ptvfsession);
    list.append(globalset.cookie_struct.ptisp);
    globalset.cookie_struct.ptui_loginuin.setName("ptui_loginuin");
    QByteArray byte_QQ;
    byte_QQ.append(globalset.string_struct.QQ_Number);
    globalset.cookie_struct.ptui_loginuin.setValue(byte_QQ);
    list.append(globalset.cookie_struct.ptui_loginuin);

    list.append(globalset.cookie_struct.pt2gguin);
    list.append(globalset.cookie_struct.superuin);
    list.append(globalset.cookie_struct.superkey);
    list.append(globalset.cookie_struct.uin);
    list.append(globalset.cookie_struct.skey);
    list.append(globalset.cookie_struct.ETK);
    list.append(globalset.cookie_struct.RK);
    list.append(globalset.cookie_struct.ptuserinfo);
    list.append(globalset.cookie_struct.ptcz);
    list.append(globalset.cookie_struct.ptwebqq);
    qDebug() << "即将发送的cookie" << list;
    QVariant var;
    var.setValue(list);
    // 发送请求
    QNetworkReply* reply = httpmethod->sendRequest(url, var);

//    QNetworkReply* reply = httpmethod->sendRequest(url, NULL);
    // 获取数据，将数据付给全局变量
    //QString context = reply->readAll();
    //qDebug() << "context---------->" << context;
    QString location = qvariant_cast<QString >(reply->header(QNetworkRequest::LocationHeader));
    qDebug() << "location------->" << location;
    getcheck_sig_url = location;

    reply->deleteLater();

}
*/

/**
 *函数名：getcheck_sig
 *作用：get方法
**/
void Widget::getcheck_sig()
{
    // url
    //QString str = "http://ptlogin4.web2.qq.com/check_sig?pttype=1&uin=xxx&service=login&nodirect=0&ptsig="+ptsig+"&s_url=http%3a%2f%2fweb2.qq.com%2floginproxy.html%3flogin2qq%3d1%26webqq%5ftype%3d10&f_url=&ptlang=2052&ptredirect=100&aid=1003903&daid=164&j_later=0&low_login_hour=0&regmaster=0";
    QString str = getcheck_sig_url;
    qDebug() << str;
    QUrl url(str);
    qDebug() << "url---------" << url;
    //cookie
    QList<QNetworkCookie> list;

    list.append(globalset.cookie_struct.ptisp);

    globalset.cookie_struct.ptui_loginuin.setName("ptui_loginuin");
    QByteArray byte_QQ;
    byte_QQ.append(globalset.string_struct.QQ_Number);
    globalset.cookie_struct.ptui_loginuin.setValue(byte_QQ);
    list.append(globalset.cookie_struct.ptui_loginuin);

    list.append(globalset.cookie_struct.pt2gguin);
    list.append(globalset.cookie_struct.uin);
    list.append(globalset.cookie_struct.skey);
    list.append(globalset.cookie_struct.RK);
    list.append(globalset.cookie_struct.ptcz);
    list.append(globalset.cookie_struct.ptwebqq);
    qDebug() << "即将发送的cookie" << list;
    QVariant var;
    var.setValue(list);
    // 发送请求
    QNetworkReply* reply = httpmethod->sendRequest(url, var);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    qDebug() << context;

    QList<QNetworkCookie> cookielist = qvariant_cast<QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
    qDebug() << "COOKIES for---------->" << cookielist;

    QNetworkCookie cookie_set;
    foreach (cookie_set, cookielist)
    {
        qDebug()<< "---------------------";
        qDebug()<< cookie_set.name() << "--------------->" << cookie_set.value();
        if(QString(cookie_set.name()) == tr("p_uin"))
        {
            if(!cookie_set.value().isEmpty())
            {
                globalset.cookie_struct.p_uin = cookie_set;
                //qDebug() << p_uin;
            }
        }else if(QString(cookie_set.name()) == tr("p_skey"))
        {
            if(!cookie_set.value().isEmpty())
            {
                globalset.cookie_struct.p_skey = cookie_set;
                //qDebug() << p_skey;
            }
        }else if(QString(cookie_set.name()) == tr("pt4_token"))
        {
            if(!cookie_set.value().isEmpty())
            {
                globalset.cookie_struct.pt4_token = cookie_set;
                //qDebug() << pt4_token;
            }
        }
    }

    reply->deleteLater();
}

/**
 *函数名：postlogin
 *  返回值：void
 *  作用：第二个login，使其它用户得知自己上线信息
**/
void Widget::postlogin()
{
    // url
    QString str = "http://d.web2.qq.com/channel/login2";
    qDebug() << "str----------->" << str;
    QUrl url(str);
    //cookie
    QList<QNetworkCookie> list;

    list.append(globalset.cookie_struct.ptisp);
    //list.append(verifysession);
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

    qDebug() << list;
    QVariant var;
    var.setValue(list);
    // postdata
    QByteArray postData;
    //QString status = "online";// 这里要控制一下
    globalset.string_struct.clientid = Tools::getRand(Tools::getRand(7, 9));

    QString strPost = "r=%7B%22status%22%3A%22online%22%2C%22ptwebqq%22%3A%22" + QString(globalset.cookie_struct.ptwebqq.value()) + "%22%2C%22passwd_sig%22%3A%22%22%2C%22clientid%22%3A%22" + globalset.string_struct.clientid + "%22%2C%22psessionid%22%3Anull%7D&clientid=" + globalset.string_struct.clientid + "&psessionid=null";
    postData.append(strPost.toUtf8());
    // 发送请求
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::CookieHeader, var);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.length());  // 设置数据的长度
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=2");

    QNetworkReply* reply = httpmethod->POSTMethod(request, postData);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;
    globalset.string_struct.psessionid = obj.value("result").toObject().value("psessionid").toString();
    qDebug() << "psessionid---------->" << globalset.string_struct.psessionid;
    globalset.string_struct.vfwebqq = obj.value("result").toObject().value("vfwebqq").toString();
    qDebug() << "vfwebqq------------->" << globalset.string_struct.vfwebqq;



}

/**
 *获取群列表
**/
void Widget::post_get_group_name_list_mask2()
{
    set_Log(QString("获取群列表"));
    // url
    QString str = "http://s.web2.qq.com/api/get_group_name_list_mask2";
    qDebug() << "str----------->" << str;
    QUrl url(str);

    //cookie
    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.ptisp);
    //list.append(verifysession);
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

    qDebug() << list;
    QVariant var;
    var.setValue(list);
    qDebug() << "var------>" << var;
    // postdata
    QByteArray postData;
    QString strPost = "r=%7B%22vfwebqq%22%3A%22" + globalset.string_struct.vfwebqq + "%22%7D";
    postData.append(strPost.toUtf8());
    qDebug() << "postdata-------------->" << postData;

    // 发送请求
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::CookieHeader, var);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");// 设置post数据的编码
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.length());  // 设置数据的长度
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3");
    qDebug() << "POSTMETHOD";
    QNetworkReply* reply = httpmethod->POSTMethod(request, postData);
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "context----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;

    QJsonArray gmasklist = obj.value("result").toObject().value("gmasklist").toArray();
    QJsonArray gnamelist = obj.value("result").toObject().value("gnamelist").toArray();
    QJsonArray gmarklist = obj.value("result").toObject().value("gmarklist").toArray();

    for(int row = 0; row < gnamelist.size(); row++)
    {
        QString gname = gnamelist[row].toObject().value("name").toString();
        for(int i = 0; i < gmarklist.size(); i++)
        {
            if(gnamelist[row].toObject().value("gid") == gmarklist[i].toObject().value("uin"))
            {
                gname = gmarklist[i].toObject().value("markname").toString();
            }
        }

        qDebug() << gname;
        ui->listWidget_GroupList->insertItem(row, new QListWidgetItem(gname));
        QVariant var;
        var.setValue(gnamelist[row].toObject());
        ui->listWidget_GroupList->item(row)->setData(Qt::UserRole, var);

        // 这里为每个群获取群好友列表
        QString code = QString::number((qulonglong)gnamelist[row].toObject().value("code").toDouble());
        // 获取群好友列表
        get_group_info_ext2(code);


    }


}

/**
 *接收线程返回的数据的槽函数
**/
void Widget::poll2ThreadSlots(QString context)
{
    qDebug() << "context---------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << obj;

    if(obj.value("retcode").toBool() != false) {qDebug() << "get poll2 data wrong"; return;}

    QJsonArray result = obj.value("result").toArray();
    qDebug() << "result----------->" << result;

    for(int row = 0; row < result.size(); row++)
    {
        QJsonObject item = result[row].toObject();
        QString poll_type = item.value("poll_type").toString();
        QJsonObject item_value = item.value("value").toObject();


        if(poll_type == QString("group_message")){
            emit group_message_Signal(item_value);
        }

    }
}

/**
 *接收群消息的槽,
**/
void Widget::group_message_Slot(QJsonObject value)
{
    // 接收到群消息，写日志，把消息提交到服务器



    QString content_text = value.value("content").toArray().last().toString();
    qDebug() << "content_text-------->" << content_text;

    // 获取uin
     QString send_uin = QString::number((qulonglong)value.value("send_uin").toDouble());

     QString from_uin = QString::number((qulonglong)value.value("from_uin").toDouble());

     // 获取昵称
     QString friend_nick;
     // 昵称
     //要先获取群好友列表，里面有昵称 和 uin的对应关系，遍历此列表，根据send_uin对应关系，获取nick
     // 获取群好友列表 需要gcode
     // 找到群号有列表 首先需要 from_uin 选择列表，然后再用send_uin选择对象，然后从对象中提取昵称
     for(QList<QJsonObject>::iterator it = Groupinfo_list.begin(); it != Groupinfo_list.end(); ++it){
         QJsonObject Groupinfo = *it;
         if(QString::number((qulonglong)Groupinfo.value("ginfo").toObject().value("gid").toDouble()) == from_uin){
             QJsonArray array_minfo = Groupinfo.value("minfo").toArray();
             for(int i = 0; i != array_minfo.size(); i++){
                 if(QString::number((qulonglong)array_minfo[i].toObject().value("uin").toDouble()) == send_uin){
                     friend_nick = array_minfo[i].toObject().value("nick").toString();
                     break;
                 }
             }
             break;
         }
     }

    // 获取QQ号
     QString friend_QQ_number = get_number(send_uin, QString("1"));


     // 获取群gid
     QString group_code = QString::number((qulonglong)value.value("group_code").toDouble());
     qDebug() << "group_code---------->" << group_code;
     // 获取群号码
     QString Group_number = get_number(group_code, QString("4"));

    // 填写发布日志
    int row = ui->tableWidget_sendlog->rowCount();
    ui->tableWidget_sendlog->insertRow(row);// 插入一行
    ui->tableWidget_sendlog->setItem(row, 0, new QTableWidgetItem(Tools::getTimeNow()));
    ui->tableWidget_sendlog->setItem(row, 1, new QTableWidgetItem(Group_number));// 这里要QQ群号
    ui->tableWidget_sendlog->setItem(row, 2, new QTableWidgetItem(friend_nick + "("+friend_QQ_number+")"));// 这里要昵称 和 QQ号 明子(xxx)
    ui->tableWidget_sendlog->setItem(row, 3, new QTableWidgetItem(content_text));// 只要群消息

    // 长度判断
    if(content_text.length() <= length_low || content_text.length() >= length_high){
        set_Log(QString("长度不合适"));
        ui->tableWidget_sendlog->setItem(row, 4, new QTableWidgetItem(QString("长度不适")));// 如果此条消息可以发布，则打对号
        return;
    }
    // 关键字判断
    if(key_list.size() != 0){
        // 设置了关键字，包含关键字的过
        bool havekey = false;
        for (QStringList::iterator it = key_list.begin();it != key_list.end(); ++it) {
            if(content_text.contains(*it)){
                havekey = true;
                break;
            }
        }
        if(!havekey){
            // 不包含关键字
            ui->tableWidget_sendlog->setItem(row, 4, new QTableWidgetItem(QString("不包含关键字")));// 如果此条消息可以发布，则打对号
            return;
        }
    }else{
        // 没有设置关键字，全部过
    }
    // 黑名单判断
    for (QStringList::iterator it = hackword_list.begin();it != hackword_list.end(); ++it) {
        if(content_text.contains(*it)){
            ui->tableWidget_sendlog->setItem(row, 4, new QTableWidgetItem(QString("有黑名单字符")));// 如果此条消息可以发布，则打对号
            return;
        }
    }
    // 替换关键字处理
    if(replease_word.isEmpty()){replease_word.append(" ");}
    for (QStringList::iterator it = hackword_list.begin();it != hackword_list.end(); ++it) {
        content_text = content_text.replace(QString(*it), replease_word);
    }
    //-------------------该判断的判断完了
    ui->tableWidget_sendlog->setItem(row, 4, new QTableWidgetItem(QString("可以发布")));// 如果此条消息可以发布，则打对号
    qDebug() << "上传的消息：" + content_text;


    // 获取电话信息
     QString tel("-");
    for (QStringList::iterator it = hackword_list.begin();it != hackword_list.end(); ++it) {
        QStringList tel_child = QString(*it).split(":");
        if(tel_child.value(0) == friend_QQ_number){
            // 附加上电话信息
            tel = tel_child.value(1);
        }
    }
    // 发布信息
    bool send_sucess = get_send_to_website(content_text, tel, friend_nick);
//这里要有个判断，判断是否发布成功
    if(send_sucess){
        ui->tableWidget_sendlog->setItem(row, 5, new QTableWidgetItem(QString("发布成功")));// 如果发布成功则打对号
    }else{
        ui->tableWidget_sendlog->setItem(row, 5, new QTableWidgetItem(QString("发布失败")));// 如果发布成功则打对号
    }


}

/**
 *关闭事件
**/
void Widget::closeEvent(QCloseEvent *e)
{
    set_Log("程序关闭");
    // 结束线程

    poll2thread->stop();
    poll2thread->exit();
    poll2thread->wait();

    saveLog();// 保存软件日志
    // 保存配置
    writeSettings();


    QWidget::closeEvent(e);

}


/**
 *关闭前保存日志
**/
void Widget::saveLog()
{
    // 将日志保存到本地
    QString content = ui->plainTextEdit_Log->toPlainText();
    qDebug() << "content---" << content;

    QString filename =Tools::getCurrentTimeStamp() + ".log";

    QDir dir(QString("./Log"));
    if(!dir.exists()){
        qDebug() << "dir.exists";
        QDir dirr(QString("."));
        dirr.mkdir(QString("Log"));
    }
    qDebug() << "filename----" << filename;
    QFile file("./Log/" + filename);
    if(file.open(QIODevice::WriteOnly)){
        qDebug() << "writeonly";
        QTextStream stream(&file);
        stream<<content;
        file.close();
    }else{
        qDebug() << "Log文件打开失败";
    }

}

/**
 *最小长度改变槽
**/
void Widget::on_spinBox_low_valueChanged(int arg1)
{
    length_low = arg1;
}

/**
 *最大值改变 槽
**/
void Widget::on_spinBox_high_valueChanged(int arg1)
{
    length_high = arg1;
}

/**
 *关键值改变
**/
void Widget::on_textEdit_keys_textChanged()
{
    key_list = ui->textEdit_keys->toPlainText().split(",");
}

/**
 *黑名单改变
**/
void Widget::on_textEdit_hackwords_textChanged()
{
    hackword_list = ui->textEdit_hackwords->toPlainText().split(",");
}

/**
 *被替换的关键字改变
**/
void Widget::on_textEdit_replease_textChanged()
{
    repleaseword_list = ui->textEdit_replease->toPlainText().split(",");
}

/**
 *用于替换的关键字改变
**/
void Widget::on_lineEdit_replease_word_textChanged(const QString &arg1)
{
    replease_word = ui->lineEdit_replease_word->text();
}

/**
 *电话信息改变
**/
void Widget::on_textEdit_tel_textChanged()
{
    tel_list = ui->textEdit_tel->toPlainText().split(",");
}

/**
 *获取好友QQ号 或群号
**/
QString Widget::get_number(QString uin, QString type)
{
    // type=1 好友QQ号
    // type=4 QQ群号
    // url
    QString str = "http://s.web2.qq.com/api/get_friend_uin2?tuin=" + uin + "&verifysession=&type=" + type + "&code=&vfwebqq="+globalset.string_struct.vfwebqq+"&t=" + Tools::getCurrentTimeStamp();
    qDebug() << "str----------->" << str;
    QByteArray byte;
    byte.append(str);
    str = str.fromLocal8Bit(byte);
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

    qDebug() << list;
    QVariant var;
    var.setValue(list);
    qDebug() << "var------>" << var;

    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::CookieHeader, var);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3");
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(request);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return NULL;}
    qDebug() << obj;

    if(obj.value("retcode").toBool() != false) {qDebug() << "get number wrong"; return NULL;}

    QString num = QString::number((qulonglong)obj.value("result").toObject().value("account").toDouble());
    qDebug() << "num----------->" << num;
    return num;
}

/**
 *提交信息到指定服务器
**/
bool Widget::get_send_to_website(QString Msg_Content, QString Msg_Tel, QString Msg_Company)
{
    QString host = ui->lineEdit_webhost->text();
    QString Msg_Code = ui->lineEdit_msg_code->text();
    //QString Msg_Content = Msg;// 这里只是单纯的消息，不加电话什么的
    //QString Msg_Tel ;//就是列表里的电话，有就加上，没有就去掉
    //QString Msg_Company ;// 这里就是QQ昵称

    // url
    QString str = host + "/estar/shareinfo/info_uploadQQ.asp?action=QQTeam_AddInfo&user=555&pwd=777&Msg_Code=" + Msg_Code + "&Msg_Type=0&Msg_Content=" + Msg_Content + "&Msg_Tel=" + Msg_Tel + "&Msg_Area=" + Msg_Code + "&Msg_StartCity=" + Msg_Code + "&Msg_Company=" + Msg_Company;
    qDebug() << "str----------->" << str;
    QUrl url;
    url.setUrl(str);
    //QByteArray byte;
    //byte.append(str);
    //url.fromEncoded(byte);
    //url.fromPercentEncoding(byte);

    QNetworkRequest request;
    request.setUrl(url);


    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(request);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;
    if(context == QString("AddOK")){
        return true;
    }else{
        return false;
    }
}


/**
 *获取群信息和群成员列表
**/
void Widget::get_group_info_ext2(QString code)
{
    //QString code = QString::number((qulonglong)var_chatBox.toJsonObject().value("code").toDouble());

    qDebug() << "code---->" << code;
    // url
    QString str = "http://s.web2.qq.com/api/get_group_info_ext2?gcode=" + code + "&cb=undefined&vfwebqq=" + globalset.string_struct.vfwebqq + "&t=" + Tools::getCurrentTimeStamp();
    qDebug() << "str----------->" << str;
    QUrl url(str);

    //cookie
    QList<QNetworkCookie> list;
    list.append(globalset.cookie_struct.ptisp);
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
    list.append(globalset.cookie_struct.ptvfsession);

    qDebug() << list;
    QVariant var;
    var.setValue(list);
    qDebug() << "var------>" << var;

    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::CookieHeader, var);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=3");
    // 发送请求
    QNetworkReply* reply = httpmethod->GETMethod(request);
    // 获取数据，将数据付给全局变量
    QString context = reply->readAll();
    reply->deleteLater();

    qDebug() << "content----------->" << context;

    QJsonObject obj;
    bool sucess = MyJson::getObject(context, obj);
    if(!sucess){qDebug() << "read json objet wrong";return;}
    qDebug() << "obj------------------->" << obj;

    if(obj.value("retcode").toBool() != false) {qDebug() << "get qun info wrong"; return;}

    //QJsonArray stats = obj.value("result").toObject().value("stats").toArray();
    //QJsonArray minfo = obj.value("result").toObject().value("minfo").toArray();
    //QJsonObject ginfo = obj.value("result").toObject().value("ginfo").toObject();

    // 将result加入列表
    Groupinfo_list.insert(Groupinfo_list.size(), obj.value("result").toObject());
}

/**
 *写配置项
**/
void Widget::writeSettings()
{
    //QSettings settings("Software Inc", "Spreadsheet"); // windows在注册表中建立建 Software Inc -> Spreadsheet
    QSettings settings("Config.ini", QSettings::IniFormat); // 当前目录的INI文件
    settings.beginGroup("Config");

    settings.setValue("replease_word", ui->lineEdit_replease_word->text());// 用于替换的关键字
    settings.setValue("replease", ui->textEdit_replease->toPlainText());// 被替换的关键字列表
    settings.setValue("hackwords", ui->textEdit_hackwords->toPlainText());// 黑名单列表
    settings.setValue("tel", ui->textEdit_tel->toPlainText());// 电话列表
    settings.setValue("keys", ui->textEdit_keys->toPlainText());// 关键字列表
    settings.setValue("webhost", ui->lineEdit_webhost->text());// 网站域名
    settings.setValue("low", ui->spinBox_low->text().toInt());// 信息长度最小值
    settings.setValue("high", ui->spinBox_high->text().toInt());// 信息长度最大值
    settings.setValue("Msg_code", ui->lineEdit_msg_code->text());// 信息发布城市

    settings.endGroup();

}

/**
 *读配置
**/
void Widget::readSettings()
{
    QSettings settings("Config.ini", QSettings::IniFormat);

    ui->lineEdit_replease_word->setText(settings.value("Config/replease_word").toString());
    ui->textEdit_replease->setPlainText(settings.value("Config/replease").toString());
    ui->textEdit_hackwords->setPlainText(settings.value("Config/hackwords").toString());
    ui->textEdit_tel->setPlainText(settings.value("Config/tel").toString());
    ui->textEdit_keys->setPlainText(settings.value("Config/keys").toString());
    ui->lineEdit_webhost->setText(settings.value("Config/webhost").toString());
    ui->spinBox_low->setValue(settings.value("Config/low").toInt());
    ui->spinBox_high->setValue(settings.value("Config/high").toInt());
    ui->lineEdit_msg_code->setText(settings.value("Config/Msg_code").toString());

}
