#include "chatbox_dockwidget.h"
#include "ui_chatbox_dockwidget.h"

chatBox_DockWidget::chatBox_DockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::chatBox_DockWidget)
{
    ui->setupUi(this);
}

chatBox_DockWidget::~chatBox_DockWidget()
{
    delete ui;
}
