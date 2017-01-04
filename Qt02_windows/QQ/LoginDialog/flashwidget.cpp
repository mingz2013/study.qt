#include "flashwidget.h"
#include <QPainter>

#include <QLabel>

#include <QMovie>

FlashWidget::FlashWidget(QString flashPath, QWidget *parent) :
    BackgroundWidget(parent)
{
    if(parent)
        this->setFixedSize(parent->size());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    flash = new QAxWidget(parent);
    flash->setFixedSize(this->size());
    flash->show();

    flash->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
    flash->dynamicCall("LoadMovie(long,string)",0, flashPath);
//    flash->dynamicCall("WMode", "transparent");

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &FlashWidget::update);
    timer->start(1000);
}

void FlashWidget::update()
{
    flash->update();
}

void FlashWidget::paintEvent(QPaintEvent *)
{

}
