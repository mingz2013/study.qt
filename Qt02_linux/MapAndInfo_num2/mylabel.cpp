#include "mylabel.h"
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setMouseTracking(true);
}


void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{   // 鼠标单击事件
    qDebug() << "mouseReleaseEvent";
    emit Clicked(this);
    QLabel::mouseReleaseEvent(ev);
}


void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "mouseMoveEvent";
    emit Move_Signals(ev->x(), ev->y());
    QLabel::mouseMoveEvent(ev);
}
