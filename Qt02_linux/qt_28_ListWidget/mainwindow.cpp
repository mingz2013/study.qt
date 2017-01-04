#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    QListWidgetItem* lst1 = new QListWidgetItem("data", ui->listWidget);
    QListWidgetItem* lst2 = new QListWidgetItem("decision", ui->listWidget);
    QListWidgetItem* lst3 = new QListWidgetItem("document", ui->listWidget);
    QListWidgetItem* lst4 = new QListWidgetItem("process", ui->listWidget);
    QListWidgetItem* lst5 = new QListWidgetItem("printer", ui->listWidget);
    */
    QListWidgetItem* lst1 = new QListWidgetItem(QIcon("images/boy.ico"), "data", ui->listWidget);
    QListWidgetItem* lst2 = new QListWidgetItem(QIcon("images/boy.ico"), "decision", ui->listWidget);
    QListWidgetItem* lst3 = new QListWidgetItem(QIcon("images/girl.ico"), "document", ui->listWidget);
    QListWidgetItem* lst4 = new QListWidgetItem(QIcon("images/girl.ico"), "process", ui->listWidget);
    QListWidgetItem* lst5 = new QListWidgetItem(QIcon("images/boy.ico"), "printer", ui->listWidget);

    /*
    QListWidgetItem* lst1 = new QListWidgetItem(QIcon("images/boy.ico"), "data");
    QListWidgetItem* lst2 = new QListWidgetItem(QIcon("images/boy.ico"), "decision");
    QListWidgetItem* lst3 = new QListWidgetItem(QIcon("images/girl.ico"), "document");
    QListWidgetItem* lst4 = new QListWidgetItem(QIcon("images/girl.ico"), "process");
    QListWidgetItem* lst5 = new QListWidgetItem(QIcon("images/boy.ico"), "printer");
    ui->listWidget->insertItem(1, lst1);
    ui->listWidget->insertItem(2, lst2);
    ui->listWidget->insertItem(3, lst3);
    ui->listWidget->insertItem(4, lst4);
    ui->listWidget->insertItem(5, lst5);
    */// 绑定选择信号
    QObject::connect(ui->listWidget, SIGNAL(currentTextChanged(const QString &)), ui->label, SLOT(setText(const QString &)));
    // 设置选项模式
    ui->listWidget->setViewMode(QListView::IconMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}
