#include "maindockwidget.h"
#include "ui_maindockwidget.h"
#include <QDebug>
#include <widget.h>

extern int num;
MainDockWidget::MainDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MainDockWidget)
{
    ui->setupUi(this);
    qDebug() << "init";
    Init();
    qDebug() << num;
}

MainDockWidget::~MainDockWidget()
{
    delete ui;
}
/*
void MainDockWidget::setVisible(bool visible)
{
   if (!visible && m_loop) {
       m_loop->exit();
   }
}

int MainDockWidget::exec()
{
    setAttribute(Qt::WA_ShowModal, true);
    show();

    QEventLoop loop;
    m_loop = &loop; //new line
    loop.exec();
    m_loop = 0; //new line
    return result();
}

*/
void MainDockWidget::Init()
{
    qDebug() << "Init()";
    //ui->dockWidgetContents->setGeometry(0, 0, 240, 500);不管用
    ui->label_MyAvatar->setGeometry(5, 5, 80, 80);
    ui->comboBox_MyStateShow->setGeometry(86, 5, 40, 27);
    //ui->label_MyNick->setGeometry(127, 5, ui->dockWidgetContents->width() - 127, 27);
    //ui->label_MySignature->setGeometry(86, 33,ui->dockWidgetContents->width() - 86, 47);
    //ui->tabWidget->setGeometry(5, 86, ui->dockWidgetContents->width(), ui->dockWidgetContents->height() - 86);

    //ui->treeWidget_BuddyList->setGeometry(ui->tab_BuddyList->x(), ui->tab_BuddyList->y() ,ui->tab_BuddyList->width(), ui->tab_BuddyList->height());

}

void MainDockWidget::resizeEvent(QResizeEvent *e)
{

    qDebug() << "resizeEvent";
    qDebug() << "ui->dockWidgetContents->width()" << ui->dockWidgetContents->width();
    qDebug() << "ui->dockWidgetContents->height()" << ui->dockWidgetContents->height();
    ui->label_MyNick->setGeometry(127, 5, ui->dockWidgetContents->width() - 127 - 5, 27);
    ui->label_MySignature->setGeometry(86, 38,ui->dockWidgetContents->width() - 86 - 5, 47);
    ui->tabWidget->setGeometry(5, 86, ui->dockWidgetContents->width() - 10, ui->dockWidgetContents->height() - 86);
    ui->treeWidget_BuddyList->setGeometry(ui->tab_BuddyList->x(), ui->tab_BuddyList->y() , ui->tab_BuddyList->width(), ui->tab_BuddyList->height() - 1);
    ui->listWidget_GroupList->setGeometry(ui->tab_BuddyList->x(), ui->tab_BuddyList->y() , ui->tab_BuddyList->width(), ui->tab_BuddyList->height() - 1);
    ui->listWidget_RecentList->setGeometry(ui->tab_BuddyList->x(), ui->tab_BuddyList->y() , ui->tab_BuddyList->width(), ui->tab_BuddyList->height() - 1);

    QDockWidget::resizeEvent(e);
}
