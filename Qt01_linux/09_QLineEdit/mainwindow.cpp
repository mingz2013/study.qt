#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nameLabel = new QLabel("user name:", this);
    nameLabel->setGeometry(QRect(QPoint(30, 10), QSize(70, 30)));

    nameEdit = new QLineEdit(this);
    nameEdit->setGeometry(QRect(QPoint(130, 10), QSize(200, 30)));
    nameEdit->setMaxLength(10);

    pswdLabel = new QLabel("passworld:", this);
    pswdLabel->setGeometry(QRect(QPoint(30, 50), QSize(70, 30)));

    pswdEdit = new QLineEdit(this);
    pswdEdit->setGeometry(QRect(QPoint(130, 50), QSize(200, 30)));
    pswdEdit->setEchoMode(QLineEdit::Password);

    readOnlyLabel = new QLabel("readOnly:", this);
    readOnlyLabel->setGeometry(QRect(QPoint(30, 90), QSize(70, 30)));

    readOnlyEdit = new QLineEdit(this);
    readOnlyEdit->setGeometry(QRect(QPoint(130, 90), QSize(200, 30)));
    readOnlyEdit->setText("hello Qt");
    readOnlyEdit->setReadOnly(true);

    validatorLabel = new QLabel("validator:",this);
    validatorLabel->setGeometry(QRect(QPoint(30, 130), QSize(70, 30)));

    validatorEdit = new QLineEdit(this);
    validatorEdit->setGeometry(QRect(QPoint(130, 130), QSize(70, 30)));
    validatorEdit->setInputMask("Dx");

    ok_btn = new QPushButton("OK", this);
    ok_btn->setGeometry(QRect(QPoint(100, 170), QSize(60, 30)));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(handleButton()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    QString username = nameEdit->text();
    QString pswd = pswdEdit->text();
    QMessageBox::information(this, "Hello Qt","userName:" + username + "\npassworld:" + pswd);
}
