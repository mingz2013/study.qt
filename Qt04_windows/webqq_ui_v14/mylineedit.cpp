#include "mylineedit.h"
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{   // 重写 失去焦点 方法

    emit focusOutSignal();

    QLineEdit::focusOutEvent(e);
}

void MyLineEdit::focusInEvent(QFocusEvent *e)
{   // 重写获取焦点方法

    emit focusInSignal();   // 发射信号

    QLineEdit::focusInEvent(e);
}
