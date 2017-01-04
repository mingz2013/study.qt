#include "verifylabel.h"

verifyLabel::verifyLabel(QWidget *parent) :
    QLabel(parent)
{
}

void verifyLabel::mouseReleaseEvent(QMouseEvent *ev)
{   // 鼠标单击事件
    emit Clicked(this);
    QLabel::mouseReleaseEvent(ev);
}
