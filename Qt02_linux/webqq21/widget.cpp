#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "myjson.h"
#include <string.h>
#include "globalset.h"

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
        ui->label_verifycode->setHidden(false);
        ui->lineEdit_verifycode->setHidden(false);
        ui->label_verifycode1->setHidden(false);
        ui->label_changeimg_link->setHidden(false);
        ui->label_imgverify->setHidden(false);

    }
    else
    {
        ui->label_verifycode->setHidden(true);
        ui->lineEdit_verifycode->setHidden(true);
        ui->label_verifycode1->setHidden(true);
        ui->label_changeimg_link->setHidden(true);
        ui->label_imgverify->setHidden(true);
    }
}

/**
 *方法名：set_showText
 *  参数1：Qstring类型
 *  作用：界面上label_show控件添加提示文本
**/
void Widget::set_showText(QString text)
{
    text = "<html><head/><body><p align=\"center\"><span style=\" color:#ff0000;\">" + text + "</span></p></body></html>";
    ui->label_show->setText(text);
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

        if(globalset.webqq->qqNumber == ui->lineEdit_QQNumber->text() && globalset.webqq->hadGetverifycode == true)
        { // 已经获取了文字验证码，
            qDebug() << "had get code";
        }else{
            // 还未获取文字验证码
            globalset.webqq->qqNumber = ui->lineEdit_QQNumber->text();
            qDebug() << "there need a GET method";
            bool need_img = globalset.webqq->getverifycode();
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
            if(globalset.webqq->textCode.length() > 4)
            {// 需要验证码
                if(ui->lineEdit_verifycode->text() == NULL)
                {// 验证码为空
                    set_showText(tr("请输入验证码"));
                    return;
                }else{
                    // 得到输入的验证码
                    globalset.webqq->textCode_write = ui->lineEdit_verifycode->text();
                }
            }

            qDebug() << "need a post method";
            //login方法-------------------写一个方法------------？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
             globalset.webqq->passwd = ui->lineEdit_password->text();
            bool b = globalset.webqq->Login();
            if(!b){return;}
            // 登录成功后载入主界面,切换窗口
            mainWidget->show();

            this->close();
            emit mainWidgetShow_signals();

        }else{
            return;
        }
    }else{
        set_showText(tr("QQ号输入为空或者错误，请重新输入"));
    }

}

/**
 *imgverify label 被单击
**/
void Widget::on_label_imgverify_Clicked(verifyLabel *)
{
   QImage image = globalset.webqq->getverifyimg();
   if (!image.isNull())
   {
       image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
       ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
   }
}

/**
 *changeimg label 被单击
**/
void Widget::on_label_changeimg_link_Clicked(verifyLabel *)
{
    QImage image = globalset.webqq->getverifyimg();
    if (!image.isNull())
    {
        image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
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
 *密码框获取焦点
**/
void Widget::on_lineEdit_password_focusInSignal()
{
    qDebug() << "focusinsignal";
       if(ui->lineEdit_QQNumber->text() != NULL)   // 输入的不为空，并且是正确的qq号,这里用正则表达式判断,都是数字，且长度限制，开头不能为0
       {
           if(globalset.webqq->qqNumber.isEmpty())
           {
               qDebug() << "QQ_Number is empty";
               goto change;
           }else{
               if(globalset.webqq->qqNumber != ui->lineEdit_QQNumber->text())
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
           set_showText(tr("QQ号输入为空或者输入错误，请重新输入"));
           return;
       }
   change:
       globalset.webqq->hadGetverifycode = false;   // 当前号码已改变
       globalset.webqq->qqNumber = ui->lineEdit_QQNumber->text();
       qDebug() << "QQ_Number----------->" + globalset.webqq->qqNumber;
       qDebug() << "focusIn, there will have a GET method";
       bool need_img = globalset.webqq->getverifycode();
       if(need_img)
       {
           qDebug() << "需要输入验证码";
           need_verifycode(true);
           QImage image = globalset.webqq->getverifyimg();
           if (!image.isNull())
           {
               qDebug() << "image not null";
               image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
               ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
           }else{
           qDebug() << "image is null";
           }
       }else{
           qDebug() << "不许要输入验证码";
           need_verifycode(false);
       }
}
