#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFormLayout>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *window = new QWidget;
    QFormLayout *formLay = new QFormLayout;
    QLineEdit *name = new QLineEdit;
    QLineEdit *password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    formLay->addRow(QObject::tr("& Name:"), name);
    formLay->addRow(QObject::tr("& password:"), password);
    window->setLayout(formLay);
    window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
