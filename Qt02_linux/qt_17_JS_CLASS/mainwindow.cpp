#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "v8_js.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    V8_JS *v8js;
    QString result = v8js->runJS(".//helloworld.js", 12, 13);
    qDebug() << "result------------------>" << result;

}

MainWindow::~MainWindow()
{
    delete ui;
}
