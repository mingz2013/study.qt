#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->treeWidget->
    //ui->treeWidget->setItemWidget();
   // QTreeWidget* treeWidget = new QTreeWidget;
     // treeWidget->setWindowTitle("QTreeWidget");
      //设定头项名称
      ui->treeWidget->setHeaderLabels(QStringList()<<"Key"<<"Value");

      ui->treeWidget->setStyleSheet("QTreeWidget::item{height:50px}");  //设置行宽,     我也找不到提供的接口  setStyleSheet很强大建议看
      ui->treeWidget->setColumnWidth(0, 100);  //设置列宽
      //设定各个项
      QTreeWidgetItem* A = new QTreeWidgetItem(QStringList()<<"A");
      A->setIcon(0, QIcon("images/boy.ico"));       // 图片文件夹应该放在编译文件夹才可以
      //A->setCheckState(0, Qt::Checked);
      QTreeWidgetItem* B = new QTreeWidgetItem(QStringList()<<"B");
      B->setIcon(0, QIcon("images/girl.ico"));
      B->setCheckState(0, Qt::Checked);
      QTreeWidgetItem* C = new QTreeWidgetItem(QStringList()<<"C");
      C->setIcon(0, QIcon("images/boy.ico"));
      C->setCheckState(0, Qt::Checked);
      ui->treeWidget->addTopLevelItem(A);
      ui->treeWidget->addTopLevelItem(B);
      ui->treeWidget->addTopLevelItem(C);



      for(int i=0; i<3; ++i)
         {
             QStringList columItemList;
             QTreeWidgetItem *child;
             QString key, value;
             key += "a" + QString::number(i);
             value += QString::number(i);
             columItemList<<key<<value;
             child = new QTreeWidgetItem(columItemList);

             child->setIcon(0, QIcon("images/girl.ico"));

             child->setBackgroundColor(0, QColor(150,0,0));// 设置背景颜色
             child->setFont(0, QFont());// 设置字体


             A->addChild(child);

         }
         A->setExpanded(true);  //展开子项
         for(int i=0; i<3; ++i)
         {
             QStringList columItemList;
             QTreeWidgetItem *child;
             QString key, value;
             key += "b" + QString::number(i);
             value += QString::number(i);
             columItemList<<key<<value;
             child = new QTreeWidgetItem(columItemList);

             //加checkbox, icon

             child->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
             child->setCheckState(0, Qt::Unchecked);
             child->setIcon(1, QIcon("images/boy.ico"));
             B->addChild(child);
         }
          B->setExpanded(true);  //展开子项
         for(int i=0; i<3; ++i)
         {
            QStringList columItemList;
             QTreeWidgetItem *child;
            QString key, value;
            key += "c" + QString::number(i);
            value += QString::number(i);
            columItemList<<key<<value;
            child = new QTreeWidgetItem(columItemList);


             C->addChild(child);

             //向ITEM里放一些QT的控件,如QSpinBox,QComboBox,QPushButton等
             ui->treeWidget->setItemWidget(child, 0, new QPushButton(this));
             ui->treeWidget->setItemWidget(child, 1, new QSpinBox(this));
         }


         /*/ 绑定数据相关
         QTreeWidgetItem* D = new QTreeWidgetItem(QStringList()<<"D");
         D->setData();
         D->data();
         ui->treeWidget->dataChanged();
         ui->treeWidget->data;
         ui->treeWidget->setUserData();
         ui->treeWidget->userData();
         ui->treeWidget->updateEditorData();
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
