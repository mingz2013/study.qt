#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *window = new QWidget;
    QPushButton *ok_btn = new QPushButton("Save");
    QPushButton *pre_btn = new QPushButton("Last step");
    QPushButton *next_btn = new QPushButton("Next step");
    QPushButton *cancel_btn = new QPushButton("Cancel");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(ok_btn);
    layout->addWidget(pre_btn);
    layout->addWidget(next_btn);
    layout->addWidget(cancel_btn);
    window->setLayout(layout);
    window->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
