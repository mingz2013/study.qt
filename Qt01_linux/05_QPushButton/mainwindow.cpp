#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    click_btn = new QPushButton("Click Button", this);// 初始化QPushButton
    click_btn->setGeometry(QRect(QPoint(100, 50), QSize(200, 50)));// 设置按钮的大小和位置
    connect(click_btn, SIGNAL(clicked()), this, SLOT(handleButton()));

    flat_btn = new QPushButton("flat Button", this);
    flat_btn->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    flat_btn->setFlat(true);// 将按钮的边缘设置成无效

    menu_btn = new QPushButton("Menu Button", this);
    menu_btn->setGeometry(QRect(QPoint(100, 150), QSize(200, 50)));
    QMenu *menu = new QMenu;
    menu->addAction("Menu_Item 1");
    menu->addAction("Menu_Item 2");
    menu->addAction("Menu_Item 3");
    menu_btn->setMenu(menu);// 为按钮添加下拉菜单选项
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    QMessageBox::information(this, "Hello Qt", "click button");
}
