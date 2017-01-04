#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <mylineedit.h>

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
    void on_lineEdit_2_mySignal(int i);

private:
    Ui::Widget *ui;
    MyLineEdit *lineEdit;
};

#endif // WIDGET_H
