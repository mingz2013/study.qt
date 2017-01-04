#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QPalette>
#include <QPixmap>
#include <QDebug>
#include <frame.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

      //setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
       //this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

      //设置背景
       QPixmap pixmap("image/Map.jpg");
       QPalette palette;
       palette.setBrush(backgroundRole(), QBrush(pixmap));
       setPalette(palette);


       f= new Frame();


       ui->label_baoding->setFrameShape(QFrame::NoFrame);
       ui->label_cangzhou->setFrameShape(QFrame::NoFrame);
       ui->label_chengde->setFrameShape(QFrame::NoFrame);
       ui->label_handan->setFrameShape(QFrame::NoFrame);
       ui->label_hengshui->setFrameShape(QFrame::NoFrame);
       ui->label_langfang->setFrameShape(QFrame::NoFrame);
       ui->label_qinhuangdao->setFrameShape(QFrame::NoFrame);
       //ui->label_shijiazhuang->setFrameShape(QFrame::NoFrame);
       ui->label_tangshan->setFrameShape(QFrame::NoFrame);
       ui->label_xingtai->setFrameShape(QFrame::NoFrame);
       ui->label_zhangjiakou->setFrameShape(QFrame::NoFrame);





}
Widget::~Widget()
{
    delete ui;
}



void Widget::on_label_chengde_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("chengde");
    if((3< x <  ui->label_chengde->width() -3) && (3 < y < ui->label_chengde->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_chengde->x() + this->x()+30, y+ui->label_chengde->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();

}

void Widget::on_label_zhangjiakou_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("zhangjiakou");
    if((3< x <  ui->label_zhangjiakou->width() -3) && (3 < y < ui->label_zhangjiakou->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_zhangjiakou->x() + this->x()+30, y+ui->label_zhangjiakou->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();

}

void Widget::on_label_qinhuangdao_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("qinhuangdao");
    if((3< x <  ui->label_qinhuangdao->width() -3) && (3 < y < ui->label_qinhuangdao->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_qinhuangdao->x() + this->x()+30, y+ui->label_qinhuangdao->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_tangshan_Move_Signals(int x, int y )
{
    qDebug() << "move signals";
    f->setCity("qinhuangdao");
    if((3< x <  ui->label_tangshan->width() -3) && (3 < y < ui->label_tangshan->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_tangshan->x() + this->x()+30, y+ui->label_tangshan->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_langfang_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("langfang");
    if((3< x <  ui->label_langfang->width() -3) && (3 < y < ui->label_langfang->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_langfang->x() + this->x()+30, y+ui->label_langfang->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_baoding_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("baoding");
    if((3< x <  ui->label_baoding->width() -3) && (3 < y < ui->label_baoding->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_baoding->x() + this->x()+30, y+ui->label_baoding->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_cangzhou_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("cangzhou");
    if((3< x <  ui->label_cangzhou->width() -3) && (3 < y < ui->label_cangzhou->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_cangzhou->x() + this->x()+30, y+ui->label_cangzhou->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_shijiazhuang_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("shijiazhuang");
    if((3< x <  ui->label_shijiazhuang->width() -3) && (3 < y < ui->label_shijiazhuang->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_shijiazhuang->x() + this->x()+30, y+ui->label_shijiazhuang->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_hengshui_Move_Signals(int x , int y)
{
    qDebug() << "move signals";
    f->setCity("hengshui");
    if((3< x <  ui->label_hengshui->width() -3) && (3 < y < ui->label_hengshui->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_hengshui->x() + this->x()+30, y+ui->label_hengshui->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_xingtai_Move_Signals(int x, int y)
{
    qDebug() << "move signals";
    f->setCity("xingtai");
    if((3< x <  ui->label_xingtai->width() -3) && (3 < y < ui->label_xingtai->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_xingtai->x() + this->x()+30, y+ui->label_xingtai->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}

void Widget::on_label_handan_Move_Signals(int x,int y)
{
    qDebug() << "move signals";
    f->setCity("handan");
    if((3< x <  ui->label_handan->width() -3) && (3 < y < ui->label_handan->height() -3) )
    {
        qDebug() << x << y;
        f->setGeometry(x + ui->label_handan->x() + this->x()+30, y+ui->label_handan->y() + this->y() + 10, 810, 455);
        f->show();
        qDebug() << "show";
    }else{
        f->hide();
        qDebug() << "hide";
    }
    //f->hide();
}
