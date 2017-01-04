#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    
signals:
    void Clicked(MyLabel *label);
    
public slots:

private:
    void mouseReleaseEvent(QMouseEvent *ev);// 点击事件
    
};

#endif // MYLABEL_H
