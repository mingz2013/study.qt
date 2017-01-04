#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "window1.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    QListWidget listWidget;
    QStackedWidget stackedWidget;
    QHBoxLayout hLayout;
    QHBoxLayout buttonLayout;
    QVBoxLayout rightLayout;
    QPushButton saveButton;
    QPushButton cancelButton;
    Window1 widget1;
    Window1 widget2;
};

#endif // WIDGET_H
