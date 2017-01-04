#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QLabel>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0/*, QLabel *label = NULL*/);
    
protected:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

private:
   // QLabel *label;
signals:
    void signal1();
    void signal2();
    
};

#endif // MYLINEEDIT_H
