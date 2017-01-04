#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QHBoxLayout>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(400, 300);
    QListWidget* listWidget = new QListWidget(this);
    listWidget->addItem(tr("Item1"));
    listWidget->addItem(tr("Item2"));
    listWidget->addItem(tr("Item3"));
    listWidget->setFixedWidth(150);
    QWidget* page1 = new QWidget(this);
    QWidget* page2 = new QWidget(this);
    QWidget* page3 = new QWidget(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(listWidget);
    QStackedLayout *stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(page1);
    stackedLayout->addWidget(page2);
    stackedLayout->addWidget(page3);
    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedLayout, SLOT(setCurrentIndex(int)));
    listWidget->setCurrentRow(0);
    hBoxLayout->addLayout(stackedLayout);
    this->setLayout(hBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
