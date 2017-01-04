#include "mylineedit.h"
#include <stdio.h>

MyLineEdit::MyLineEdit(QWidget *parent, QLabel *label) :
    QLineEdit(parent)
{
    this->label = label;
}
void MyLineEdit::focusInEvent(QFocusEvent *e)
{
    printf("focusInEvent\n");
    label->setText(tr("focusInEvent"));
    QLineEdit::focusInEvent(e);
}
void MyLineEdit::focusOutEvent(QFocusEvent *e)
{
    printf("focusOutEvent\n");
    label->setText(tr("focusOutEvent"));
    QLineEdit::focusOutEvent(e);
}
