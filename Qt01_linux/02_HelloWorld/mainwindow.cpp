// mainwindow.cpp
// helloworld工程主创口类源文件
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>
#include <QTimer>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建文本编辑组件，并将其设置成程序主工作区控件
    m_QtextEdit = new QTextEdit;
    // 设置文本编辑组件可以接受并显示副文本
    m_QtextEdit->setAcceptRichText(true);
    // 设置文本编辑组件为程序的主窗口控件
    setCentralWidget(m_QtextEdit);
    // 设置主窗口的初始化槽
    QTimer::singleShot(0, this, SLOT(slotInitializeTextEdit()));
}

MainWindow::~MainWindow()
{   // 释放资源
    delete ui;
}

void MainWindow::slotInitializeTextEdit()
{
    // 设置文本编辑组件的背景颜色为亮灰色（Qt::lightGray）
    m_QtextEdit->setTextBackgroundColor(QColor(Qt::lightGray));
    // 向文本编辑组件添加纯文本记录
    m_QtextEdit->insertPlainText(tr("Hello world\n"));
    // 向文本编辑组件添加简单的HTML文本记录
    m_QtextEdit->insertHtml("<b>Hello world<b>");
    m_QtextEdit->insertPlainText("\n");
    // 构造复杂的HTML记录
    QString qstrRichText;
    qstrRichText = tr("<img src = \"%1/images/Qt.png\">").arg(QApplication::applicationDirPath());
    m_QtextEdit->insertHtml(qstrRichText + "Hello World" + qstrRichText);
}
