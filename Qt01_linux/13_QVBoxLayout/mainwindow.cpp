#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *window = new QWidget;
    QButtonGroup *btnGroup = new QButtonGroup(window);
    QRadioButton *rBtn1 = new QRadioButton("ONE");
    QRadioButton *rBtn2 = new QRadioButton("TWO");
    QRadioButton *rBtn3 = new QRadioButton("THREE");
    btnGroup->addButton(rBtn1);
    btnGroup->addButton(rBtn2);
    btnGroup->addButton(rBtn3);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(rBtn1);
    layout->addWidget(rBtn2);
    layout->addWidget(rBtn3);
    window->setLayout(layout);
    window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
