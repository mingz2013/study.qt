#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{

}


void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{   // 鼠标单击事件
    emit Clicked(this);
    QLabel::mouseReleaseEvent(ev);
}
