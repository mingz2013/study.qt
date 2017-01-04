#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMouseEvent>
#include <QDebug>
#include "globalset.h"




extern GlobalSet globalset;// 引用全局变量

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    needVerifyCode(false);



}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/**
 *方法名：set_showText
 *  参数1：Qstring类型
 *  作用：界面上label_show控件添加提示文本
**/
void LoginDialog::set_showText(QString text)
{
    text = "<html><head/><body><p align=\"center\"><span style=\" color:#ff0000;\">" + text + "</span></p></body></html>";
    ui->label_show->setText(text);
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
}

void LoginDialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

void LoginDialog::needVerifyCode(bool need){
    int changesize = 100;
    if(need){
        ui->widget_VerifyCode->setHidden(false);
        ui->pushButton_Login->move(ui->pushButton_Login->x(), 330);
        ui->comboBox_Status->move(ui->comboBox_Status->x(), 345);
        ui->stackedWidget->setGeometry(ui->stackedWidget->x(), ui->stackedWidget->y(), ui->stackedWidget->width(), 400);

    }else{
        ui->widget_VerifyCode->setHidden(true);
        ui->pushButton_Login->move(ui->pushButton_Login->x(), 330 - changesize);
        ui->comboBox_Status->move(ui->comboBox_Status->x(), 345 - changesize);
        ui->stackedWidget->setGeometry(ui->stackedWidget->x(), ui->stackedWidget->y(), ui->stackedWidget->width(), 400 - changesize);
    }
}


void LoginDialog::on_pushButton_Setting_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_Setting->setHidden(true);
}

void LoginDialog::on_pushButton_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_Setting->setHidden(false);
}

void LoginDialog::on_pushButton_Right_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_Setting->setHidden(false);
}

void LoginDialog::on_pushButton_Minisize_clicked()
{
    this->setHidden(true);
}

void LoginDialog::on_pushButton_Close_clicked()
{
    this->close();
}
void LoginDialog::on_lineEdit_QQNumber_focusOutSignal()
{
    ui->lineEdit_QQNumber->setText(ui->lineEdit_QQNumber->text().trimmed());
}

void LoginDialog::on_lineEdit_Password_focusInSignal()
{
    qDebug() << "focusinsignal";
    if(ui->lineEdit_QQNumber->text() != NULL)   // 输入的不为空，并且是正确的qq号,这里用正则表达式判断,都是数字，且长度限制，开头不能为0
    {
        set_showText("");
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
        needVerifyCode(true);
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
        needVerifyCode(false);
    }

}

void LoginDialog::on_label_imgverify_Clicked(verifyLabel *)
{
    QImage image = globalset.webqq->getverifyimg();
    if (!image.isNull())
    {
        image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
    }
}

void LoginDialog::on_label_ChangeImg_Clicked(verifyLabel *)
{

    QImage image = globalset.webqq->getverifyimg();
    if (!image.isNull())
    {
        image = image.scaled(ui->label_imgverify->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_imgverify->setPixmap(QPixmap::fromImage(image));
    }
}

void LoginDialog::on_pushButton_Login_clicked()
{
    if(NULL != ui->lineEdit_QQNumber->text())
    {
        bool allright = true;
        if(NULL != ui->lineEdit_Password->text())
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
                if(ui->lineEdit_Verifycode->text() == NULL)
                {// 验证码为空
                    set_showText(tr("请输入验证码"));
                    return;
                }else{
                    // 得到输入的验证码
                    globalset.webqq->textCode_write = ui->lineEdit_Verifycode->text();
                }
            }

            qDebug() << "need a post method";
            //login方法-------------------写一个方法------------？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
            globalset.webqq->passwd = ui->lineEdit_Password->text();
            bool b = globalset.webqq->Login();
            if(!b){return;}
            // 登录成功后载入主界面,切换窗口
            maindialog->show();

            this->close();
            emit mainDialogShow_signals();

        }else{
            return;
        }
    }else{
        set_showText(tr("QQ号输入为空或者错误，请重新输入"));
    }
}




