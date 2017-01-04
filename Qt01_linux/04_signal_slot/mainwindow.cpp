#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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
void MainWindow::on_m_btn_connect_clicked()
{
    connect(ui->m_edit_input, SIGNAL(textChanged(const QString&)), ui->m_edit_show, SLOT(setText(const QString&)));
    connect(ui->m_edit_input, SIGNAL(textChanged(const QString&)), ui->m_edit_show_2, SLOT(setText(const QString&)));
    connect(ui->m_edit_input, SIGNAL(textChanged(const QString&)), ui->m_edit_show_3, SLOT(setText(const QString&)));
}
void MainWindow::on_m_btn_disconnect_clicked()
{
    disconnect(ui->m_edit_input, 0, 0, 0);
}
