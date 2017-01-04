#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "v8_js.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    V8_JS *v8js = new V8_JS(this);



    int argc = 3;
    const string argv[] = {"aaa", "aaaaaaaaaaaa", "aaaaaaaaaaa"};

    QString md5_passwd = v8js->runJS("./JS/QQ.js", "func", argc, argv);
    qDebug() << "md5_passwd----------------->" << md5_passwd;

}
