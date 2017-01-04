#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    
signals:
    void Clicked(MyLabel *label);
    void Move_Signals(int x, int y);
    
public slots:

private:
    void mouseReleaseEvent(QMouseEvent *ev);// 点击事件

    void mouseMoveEvent(QMouseEvent *ev);

    
};

#endif // MYLABEL_H
