#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QImageReader>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    if(path.startsWith("http"))
    {
        QNetworkRequest request;
        QString url = ui->lineEdit->text();
        request.setUrl(url);
        manager->get(request);
    }
    else
    {
        // [[4]]: 在label上显示图片
        QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
        if (!image.isNull()) {
            image = image.scaled(
                    ui->label->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                    );
        ui->label->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return;
    }
    // Example 1: Creating QImage from the reply
    QImageReader imageReader(reply);
    QImage image = imageReader.read();
    if (!image.isNull()) {
        image = image.scaled(
                ui->label->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                );
    ui->label->setPixmap(QPixmap::fromImage(image));
    }
}
