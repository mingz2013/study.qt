#include "pushbutton.h"

#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QLabel>

PushButton::PushButton(QString normal, QString hover, QString pressed, QWidget *parent) :
    QPushButton(parent)
{
    buttonState = Normal;

    normalPixmap.load(normal);
    hoverPixmap.load(hover);
    pressPixmap.load(pressed);

    this->setFixedSize(normalPixmap.size());

    this->setContentsMargins(0, 0, 0, 0);
}

PushButton::PushButton(QString background, QWidget *parent) :
    QPushButton(parent)
{
    buttonState = Normal;

    normalPixmap.load(background);
    hoverPixmap.load(background);
    pressPixmap.load(background);

    this->setFixedSize(normalPixmap.size());

    this->setContentsMargins(0, 0, 0, 0);
}

void PushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch(buttonState)
    {
    case Normal:
        painter.drawPixmap(this->rect(), normalPixmap);
        break;
    case Hover:
        painter.drawPixmap(this->rect(), hoverPixmap);
        break;
    case Pressed:
        painter.drawPixmap(this->rect(), pressPixmap);
    }

    painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}

void PushButton::enterEvent(QEvent *)
{
    buttonState = Hover;
    update();
}

void PushButton::leaveEvent(QEvent *)
{
    buttonState = Normal;
    update();
}

void PushButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        buttonState = Pressed;
        update();
    }
}

bool isOnPushButton(const QPoint &point, const PushButton *pushButton)
{
    if(point.x() < 0 || point.x() > pushButton->width() ||
            point.y() < 0 || point.y() > pushButton->height())
    {
        return false;
    }
    return true;
}

void PushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //判断鼠标抬起时是否在PushButton之上
        if(isOnPushButton(e->pos(), this))
        {
            emit clicked();
        }

        buttonState = Hover;
        update();
    }
}
