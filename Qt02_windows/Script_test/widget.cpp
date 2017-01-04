#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);



   // QLineEdit *edit = new QLineEdit();
    handler = eng.evaluate("(function(text) { print('text was changed to', text); })");
    qScriptConnect(ui->lineEdit, SIGNAL(textChanged(const QString &)), QScriptValue(), handler);

}

Widget::~Widget()
{
    delete ui;
}
