#ifndef VERIFYLABEL_H
#define VERIFYLABEL_H

#include <QLabel>

/**
 *复写的QLabel类
**/
class verifyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit verifyLabel(QWidget *parent = 0);
    
signals:
    void Clicked(verifyLabel *label);
    
public slots:

private:
    void mouseReleaseEvent(QMouseEvent *ev);// 点击事件

    
};

#endif // VERIFYLABEL_H
