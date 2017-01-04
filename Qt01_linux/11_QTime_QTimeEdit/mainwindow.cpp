#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentLabel = new QLabel("editTime:", this);
    currentLabel->setGeometry(50, 20, 150, 30);

    timeNow = QTime::currentTime();

    timeEdit = new QTimeEdit(timeNow, this);
    timeEdit->setDisplayFormat("h::mm::ss");
    timeEdit->setGeometry(160, 20, 200, 30);
    timeEdit->setTimeRange(timeNow.addSecs(60), timeNow.addMSecs(60*3));

    click_btn = new QPushButton("Get Timer", this);
    click_btn->setGeometry(QRect(QPoint(100, 60), QSize(80, 30)));

    connect(click_btn, SIGNAL(clicked()), this, SLOT(handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{

    QString strTimeCurrent = QTime::currentTime().toString("hh:mm:s");
    QString strTimeNow = timeNow.toString("hh:mm:ss");
    QString strTimeEdit = timeEdit->time().toString("hh:mm:ss");

    int h = timeNow.hour();
    int m = timeNow.minute();
    int s = timeNow.second();

    QMessageBox::information(this, "hello Qt", "Timer Now:" + strTimeNow + "\n"
                             + "editTime:" + strTimeEdit + "\n"
                             + "current time:" + strTimeCurrent);
}
