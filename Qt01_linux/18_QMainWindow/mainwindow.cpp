#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *fileNewAction = new QAction("fileNewAction", this);
    fileNewAction->setText(tr("新建"));

    QMenu *fileMenu = new QMenu(this);
    fileMenu->addAction(fileNewAction);

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->addMenu(fileMenu);

    connect(fileNewAction, SIGNAL(activated()), this, SLOT(fileNew()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fileNew()
{
    QMessageBox::information(this, "hello qt", "this is a menu");
}
