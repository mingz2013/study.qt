#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    QLabel *nameLabel = new QLabel("name");
    QLabel *pswdLabel = new QLabel("password");
    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *pswdEdit = new QLineEdit();
    layout->addWidget(nameLabel, 0, 0, 1, 1);
    layout->addWidget(nameEdit, 0, 1, 1, 1);
    layout->addWidget(pswdLabel, 1, 0, 1, 1);
    layout->addWidget(pswdEdit, 1, 1, 1, 1);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QGroupBox *gb = new QGroupBox("QGridLayout");
    gb->setLayout(layout);
    mainLayout->addWidget(gb);
    widget->setLayout(mainLayout);
    widget->layout()->setSizeConstraint(QLayout::SetFixedSize);
    widget->show();
}

Widget::~Widget()
{
    delete ui;
}
