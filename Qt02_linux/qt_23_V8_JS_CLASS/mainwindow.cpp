#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "v8_js.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    V8_JS *js = new V8_JS(this);
    //qDebug() << js->runJS(".//helloworld.js", "abc", "def", "ghi");//"\x00\x00\x00\x00\x12\x37\x24\x51");
    qDebug() << js->runJS(".//QQ.js", "ahzosdks2342", "!ADS", "\x00\x00\x00\x00\x12\x37\x24\x51");
}

MainWindow::~MainWindow()
{
    delete ui;
}
