#include "toolwidget.h"

#include <QHBoxLayout>

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent)
{
    createUI();
    setUILayout();
    setConnect();

    retranslateUI();
}

void ToolWidget::setConnect()
{
    connect(settingButton, &PushButton::clicked, this, &ToolWidget::setting_clicked);
    connect(minimizeButton, &PushButton::clicked, this, &ToolWidget::minimize_clicked);
    connect(closeButton, &PushButton::clicked, this, &ToolWidget::close_clicked);
}

void ToolWidget::createUI()
{
    settingButton = new PushButton(":/button/btn_set_normal",
                                   ":/button/btn_set_hover",
                                   ":/button/btn_set_pressed", this);

    minimizeButton = new PushButton(":/button/minimize",
                                    ":/button/minimize_hover",
                                    ":/button/minimize_pressed", this);

    closeButton = new PushButton(":/button/close",
                                 ":/button/close_hover",
                                 ":/button/close_pressed", this);
}

void ToolWidget::setUILayout()
{
    //图片问题，这里不使用布局，直接 定位
//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(settingButton, 0, Qt::AlignTop);
//    layout->addWidget(minimizeButton, 0, Qt::AlignTop);
//    layout->addWidget(closeButton, 0, Qt::AlignTop);
//    layout->setSpacing(0);
//    layout->setContentsMargins(0, 0, 0, 0);

//    this->setLayout(layout);

    settingButton->setGeometry(0, -2, settingButton->width(), settingButton->height());
    minimizeButton->setGeometry(settingButton->width()-1, -1, minimizeButton->width(), minimizeButton->height());
    closeButton->setGeometry(settingButton->width()-3 + minimizeButton->width(), -1, closeButton->width(), closeButton->height());
    this->setFixedSize(settingButton->width() + minimizeButton->width() + closeButton->width()-4, closeButton->height()-2);
}

void ToolWidget::retranslateUI()
{
    settingButton->setToolTip(tr("Setting"));
    minimizeButton->setToolTip(tr("Minimize"));
    closeButton->setToolTip(tr("Close"));
}
