#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // 下载按钮
{
    url = ui->lineEdit->text();
    //获取在界面中输入的url地址，如： http://zz.onlinedown.net/down/laolafangkuaijin.rar
    qDebug() << url;
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    qDebug() << fileName;
    //获取文件名
    if (fileName.isEmpty())
    {
        fileName = "index.html";
    }
    //如果文件名为空，则使用“index.html”，
    //例如使用“http://www.yafeilinux.com”时，文件名就为空
    qDebug() << fileName;
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        //如果打开文件失败，则删除file，并使file指针为0，然后返回
        qDebug() << "file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);  //进行链接请求
    ui->progressBar->setValue(0);  //进度条的值设为0
    ui->progressBar->show();  //显示进度条
}

void MainWindow::startRequest(QUrl url)  //链接请求
{
    reply = manager->get(QNetworkRequest(url));
    //下面关联信号和槽
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));  //下载完成后
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));  //有可用数据时
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgress(qint64,qint64)));  //更新进度条
}

void MainWindow::httpReadyRead()   //有可用数据
{
    if (file){
        file->write(reply->readAll());  //如果文件存在，则写入文件
    }else
    {
        qDebug() << "文件不存在";
    }
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
 {
    ui->progressBar->setMaximum(totalBytes); //最大值
    ui->progressBar->setValue(bytesRead);  //当前值
    qDebug() << bytesRead;
}

void MainWindow::httpFinished()  //完成下载
{
    ui->progressBar->hide();
    file->flush();
    qDebug() << file->fileName();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;

}

void MainWindow::on_pushButton_2_clicked()// 终止下载按钮
{
    qDebug() << tr("Download canceled.");
    //httpRequestAborted = true;
    reply->abort();
    ui->pushButton_2->setEnabled(true);
}
