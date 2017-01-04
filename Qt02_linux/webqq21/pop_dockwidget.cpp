#include "pop_dockwidget.h"
#include "ui_pop_dockwidget.h"

Pop_DockWidget::Pop_DockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Pop_DockWidget)
{
    ui->setupUi(this);
}

Pop_DockWidget::~Pop_DockWidget()
{
    delete ui;
}
