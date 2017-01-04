#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // 初始化
    ui->setupUi(this);

    btnGroup = new QButtonGroup(this);

    rb1 = new QRadioButton("Black");
    rb2 = new QRadioButton("Red");

    btnGroup->addButton(rb1);
    btnGroup->addButton(rb2);

    rb1->setChecked(true);
    btnGroup->setExclusive(true);

    gb = new QGroupBox("Colors");
    layout = new QGridLayout();
    layout->addWidget(rb1, 0, 0, 1, 1);
    layout->addWidget(rb2, 0, 1, 1, 1);
    gb->setLayout(layout);

    m_QtextEdit = new QTextEdit;
    m_QtextEdit->setText("This document introduces Qt Assisant, a tool for presenting on-linedocumentation");

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(gb);
    mainLayout->addWidget(m_QtextEdit);
    this->setLayout(mainLayout);
    // ...........................................还有错误..........................
    //QWidget::setLayout: Attempting to set QLayout "" on MainWindow "MainWindow", which already has a layout
    /*
    QWidget * widget = new QWidget(this);
    widget->setLayout(layout);
    this->setCentralWidget(widget);
    */

    connect(btnGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(changeCurrentIndex(QAbstractButton*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 改变颜色
void MainWindow::changeCurrentIndex(QAbstractButton *btn1)
{
    if(btn1->text() == "Black")
    {
        m_QtextEdit->setTextColor(QColor(Qt::black));

    } else
    {
        if(btn1->text() == "Red")
        {
            m_QtextEdit->setTextColor(QColor(Qt::red));
        }
    }
}
