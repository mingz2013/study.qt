#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QPalette>
#include <QPixmap>
#include "form_info.h"

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

void Widget::on_label_chengde_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("chengde");
    info_form->show();
}

void Widget::on_label_zhangjiakou_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("zhangjiakou");
    info_form->show();
}

void Widget::on_label_qinhuangdao_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("qinhuangdao");
    info_form->show();
}

void Widget::on_label_tangshan_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("tangshan");
    info_form->show();

}

void Widget::on_label_langfang_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("langfang");
    info_form->show();
}

void Widget::on_label_baoding_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("baoding");
    info_form->show();
}

void Widget::on_label_cangzhou_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("cangzhou");
    info_form->show();
}

void Widget::on_label_shijiazhuang_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("shijiazhuang");
    info_form->show();
}

void Widget::on_label_hengshui_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("hengshui");
    info_form->show();
}

void Widget::on_label_xingtai_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("xingtai");
    info_form->show();
}

void Widget::on_label_handan_Clicked(MyLabel *)
{
    Form_Info *info_form = new Form_Info("handan");
    info_form->show();
}
