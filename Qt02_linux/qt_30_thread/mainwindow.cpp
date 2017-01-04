#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMutex>


extern int p[10];
extern int i;
extern int a;
extern QMutex mutex;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mythread = new MyThread(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mythread->start();

    while(true){
        mutex.lock();
        if(a < i){
            int b = p[a];
            qDebug() << "b------>" << b;
            a++;
            if(a == 11)
            {
                a = 0;
            }

        }
        mutex.unlock();
        QThread::sleep(2);
   }
}

void MainWindow::on_pushButton_2_clicked()
{
   mythread->deleteLater();
}
