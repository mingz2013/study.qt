#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    nam = new QNetworkAccessManager(this);

    HideWidgets();

    connect(ui->getButton,SIGNAL(clicked()),this,SLOT(activateGetWidgets()));
    connect(ui->submitButton,SIGNAL(clicked()),this,SLOT(DoHttpGet()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(clearWidgets()));
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    connect(ui->postButton,SIGNAL(clicked()),this,SLOT(activatePostWidgets()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e) // 复写方法，当控件改变时，刷新界面
{
    QMainWindow::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::activateGetWidgets()
{
    ui->urlLabel->setHidden(false);
    ui->urlLine->setHidden(false);
    ui->submitButton->setHidden(false);
    ui->textBrowser->setHidden(false);
    ui->responseTitleLabel->setHidden(false);
    ui->getButton->setHidden(true);
    ui->postButton->setHidden(true);
}

void MainWindow::activatePostWidgets()
{
    ui->dataLabel->setHidden(false);
    ui->dataLine->setHidden(false);
    activateGetWidgets();
}

void MainWindow::finished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        ui->textBrowser->setText(reply->readAll());
    }
    else
    {
        ui->textBrowser->setText(reply->errorString());
    }
}

void MainWindow::DoHttpGet()
{
    ui->resetButton->setHidden(false);
    QString url = ui->urlLine->text();
    QString data = ui->dataLine->text();
    QByteArray postData;

    //postData.append(data.toAscii());
    postData.append(data.toUtf8());

    if(postData.isEmpty() == true)
    {
        nam->get(QNetworkRequest(QUrl(url)));
    }
    else
    {
        nam->post(QNetworkRequest(QUrl(url)),postData);
    }
}

void MainWindow::HideWidgets()
{
    ui->urlLabel->setHidden(true);
    ui->urlLine->setHidden(true);
    ui->dataLabel->setHidden(true);
    ui->dataLine->setHidden(true);
    ui->submitButton->setHidden(true);
    ui->responseTitleLabel->setHidden(true);
    ui->textBrowser->setHidden(true);
    ui->resetButton->setHidden(true);
}

void MainWindow::clearWidgets()
{
    ui->urlLabel->setHidden(true);
    ui->urlLine->setHidden(true);
    ui->dataLabel->setHidden(true);
    ui->dataLine->setHidden(true);
    ui->submitButton->setHidden(true);
    ui->responseTitleLabel->setHidden(true);
    ui->textBrowser->setHidden(true);
    ui->resetButton->setHidden(true);
    ui->urlLine->clear();
    ui->textBrowser->clear();
    ui->dataLine->clear();
    ui->getButton->setHidden(false);
    ui->postButton->setHidden(false);
}
