#include "dialog.h"
#include "ui_dialog.h"
#include <QVBoxLayout>
#include <QFormLayout>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    InitWidget1();
    InitWidget2();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(widget1);
    layout->addWidget(widget2);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->addSpacing(8);
    this->setLayout(layout);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::InitWidget1()
{
    widget1 = new QWidget;
    QFormLayout *formLay = new QFormLayout;
    name = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    formLay->addRow(QObject::tr("&Name:"), name);
    formLay->addRow(QObject::tr("&password:"), password);
    QHBoxLayout *hlayout = new QHBoxLayout;
    loginBtn = new QPushButton("OK");
    detailBtn = new QPushButton("Show");
    hlayout->addWidget(loginBtn);
    hlayout->addWidget(detailBtn);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(formLay);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(vlayout);
    QObject::connect(detailBtn, SIGNAL(clicked()), this, SLOT(show11()));
}

void Dialog::InitWidget2()
{
    widget2 = new QWidget;
    rb1 = new QRadioButton("Admin");
    rb2 = new QRadioButton("Custom");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(rb1, 0, 0, 1, 1);
    layout->addWidget(rb2, 0, 1, 1, 1);
    widget2->setLayout(layout);
    widget2->hide();
}

void Dialog::show11()
{
    if (widget2->isHidden()) {

        widget2->show();
        detailBtn->setText("hide");

    } else {

        widget2->hide();
        detailBtn->setText("show");
    }
}
