#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mylabel.h"

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
    void on_label_chengde_Clicked(MyLabel *);

    void on_label_zhangjiakou_Clicked(MyLabel *);

    void on_label_qinhuangdao_Clicked(MyLabel *);

    void on_label_tangshan_Clicked(MyLabel *);

    void on_label_langfang_Clicked(MyLabel *);

    void on_label_baoding_Clicked(MyLabel *);

    void on_label_cangzhou_Clicked(MyLabel *);

    void on_label_shijiazhuang_Clicked(MyLabel *);

    void on_label_hengshui_Clicked(MyLabel *);

    void on_label_xingtai_Clicked(MyLabel *);

    void on_label_handan_Clicked(MyLabel *);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
