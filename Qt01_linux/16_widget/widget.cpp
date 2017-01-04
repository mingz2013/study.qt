#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStyleSheet(QString::fromUtf8("layout1{background-color:rgb(51, 204, 204);}"));
    /*连接信号*/
    connect(&listWidget, SIGNAL(currentRowChanged(int)),
            & stackedWidget, SLOT(setCurrentIndex(int)));
    /*初始化按钮*/
    saveButton.setText("save");
    cancelButton.setText("cancel");
    buttonLayout.addWidget(& saveButton);
    buttonLayout.addWidget(& cancelButton);
    /*初始化各部件*/
    listWidget.addItem(tr("base"));
    listWidget.addItem(tr("detail"));
    stackedWidget.addWidget(& widget1);
    stackedWidget.addWidget(& widget2);
    stackedWidget.setCurrentIndex(1);
    rightLayout.addWidget(& stackedWidget);
    rightLayout.addLayout(& buttonLayout);
    hLayout.addWidget(& listWidget, 1);
    hLayout.addLayout(& rightLayout, 3);
    setLayout(& hLayout);
}

Widget::~Widget()
{
    delete ui;
}
