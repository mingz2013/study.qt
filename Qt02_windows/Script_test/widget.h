#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

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
    QScriptEngine eng;
    QScriptValue handler;
};

#endif // WIDGET_H
