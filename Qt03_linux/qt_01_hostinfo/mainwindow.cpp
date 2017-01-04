#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHostInfo>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitWidget1();
    InitWidget2();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(widget1);
    layout->addWidget(widget2);

    layout->setSizeConstraint(QLayout::SetFixedSize);//------------------------????????????????
    layout->addSpacing(8);                              //---------------------??????????????????

    this->setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitWidget1()
{
    widget1 = new QWidget;
    QFormLayout *formLay = new QFormLayout;
    name = new QLineEdit;
    ip = new QLineEdit;
    name->setReadOnly(true);
    ip->setReadOnly(true);

    QString hostName = QHostInfo::localHostName();//---------------------------------------------
    QHostInfo hostinfo = QHostInfo::fromName(hostName);
    QList<QHostAddress> listAddress = hostinfo.addresses();
    if(!listAddress.isEmpty())
    {
        ip->setText(listAddress.first().toString());
    }
    //----------------------------------------------------------------------------------------------


    name->setText(hostName);
    detailBtn = new QPushButton("Detail");
    formLay->addRow(QObject::tr("&Name:"), name);
    formLay->addRow(QObject::tr("&IP:"), ip);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(formLay);
    vlayout->addWidget(detailBtn);
    widget1->setLayout(vlayout);

    QObject::connect(detailBtn, SIGNAL(clicked()), this, SLOT(show11()));
}

void MainWindow::InitWidget2()
{
    widget2 = new QWidget;
    QString str = "";

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();//-----------------------------------
    // 获取所有网络接口的列表
    foreach (QNetworkInterface interface, list) {
        // 便利每一个网络接口
        str = str + "Device:" + interface.name() + "\n";
        // 设备名
        str = str + "HardwareAddress:" + interface.hardwareAddress() + "\n";
        // 硬件地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        // 获取IP地址条目列表，条目中包含一个IP地址，一个子网眼吗，一个广播地址
        foreach (QNetworkAddressEntry entry, entryList) {
            // 遍历每一个IP地址条目
            str = str + "\t" + "IP Address:" + entry.ip().toString() + "\n";
            str = str + "\t" + "Netmask:" + entry.netmask().toString() + "\n";
            str = str + "\t" + "Broadcast:" + entry.broadcast().toString() + "\n";
        }
    }//------------------------------------------------------------------------------------------------------


    QHBoxLayout *hlayout = new QHBoxLayout;
    detail = new QTextEdit(this);
    detail->setPlainText(str);
    hlayout->addWidget(detail);
    widget2->setLayout(hlayout);
    widget2->hide();
}


void MainWindow::show11()
{
    if(widget2->isHidden()){
        widget2->show();
        detailBtn->setText("Hide");
    }else{
        widget2->hide();
        detailBtn->setText("Detail");
    }
}
