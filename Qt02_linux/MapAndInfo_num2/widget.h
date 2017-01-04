#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mylabel.h"
#include <frame.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:


    void on_label_chengde_Move_Signals(int x, int y);

    void on_label_zhangjiakou_Move_Signals(int , int );

    void on_label_qinhuangdao_Move_Signals(int , int);

    void on_label_tangshan_Move_Signals(int , int );

    void on_label_langfang_Move_Signals(int , int );

    void on_label_baoding_Move_Signals(int , int );

    void on_label_cangzhou_Move_Signals(int , int );

    void on_label_shijiazhuang_Move_Signals(int , int );

    void on_label_hengshui_Move_Signals(int , int );

    void on_label_xingtai_Move_Signals(int , int );

    void on_label_handan_Move_Signals(int , int );

private:
    Ui::Widget *ui;
    Frame *f ;
};

#endif // WIDGET_H
