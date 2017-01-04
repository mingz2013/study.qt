#ifndef QQNUMBERLINEEDIT_H
#define QQNUMBERLINEEDIT_H

#include <QLineEdit>

/**
 *复写的QLineEdit类
**/
class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);
    
signals:
    void focusOutSignal();
    void focusInSignal();
    
public slots:

private:
    void focusInEvent(QFocusEvent *e);  // 重写获取焦点函数
    void focusOutEvent(QFocusEvent *e); // 重写失去焦点方法
    
};

#endif // QQNUMBERLINEEDIT_H
