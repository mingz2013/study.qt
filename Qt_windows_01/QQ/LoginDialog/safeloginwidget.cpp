#include "safeloginwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPainter>

SafeLoginWidget::SafeLoginWidget(QWidget *parent) :
    QWidget(parent)
{
    if(parent)
        this->setFixedSize(parent->size());

    createUI();
    setUILayout();
    setConnect();

    retranslateUI();
}

void SafeLoginWidget::setConnect()
{
    connect(cancelButton, &PushButton::clicked, this, &SafeLoginWidget::cancel_clicked);
}

void SafeLoginWidget::createUI()
{
    safeLabel = new QLabel();
    safeLabel->setPixmap(QPixmap(":/safe/client_trust_small"));

    titleLabel = new QLabel();

    infoLabel = new QLabel();

    qrCodeLabel = new QLabel();
    qrCodeLabel->setPixmap(QPixmap(":/qrcode/qr_default"));

    cancelButton = new PushButton(":/button/login_button_normal",
                                 ":/button/login_button_hover",
                                 ":/button/login_button_pressed");
}

void SafeLoginWidget::setUILayout()
{
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addWidget(safeLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    titleLayout->addWidget(titleLabel, 0 , Qt::AlignTop);
    titleLayout->setContentsMargins(2, 2, 280, 0);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(infoLabel, 0, Qt::AlignHCenter);
    vLayout->addSpacing(10);
    vLayout->addWidget(qrCodeLabel, 0, Qt::AlignHCenter);
    vLayout->setContentsMargins(0, 0, 0, 20);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(titleLayout);
    layout->addLayout(vLayout);
    layout->addWidget(cancelButton, 0, Qt::AlignHCenter);
    layout->setContentsMargins(0, 0, 0, 5);

    this->setLayout(layout);
}

void SafeLoginWidget::retranslateUI()
{
    titleLabel->setText(tr("Safe Login"));

    safeManagerUrl = "http://m.qq.com/?isFromPCQQ=true&g_bid=946";
    knowMoreUrl = "http://m.qq.com/secure_login/index.jsp?isFromPCQQ=true&g_f=23411&g_bid=944";

    infoLabel->setText(tr("Using") + "<a href='" + safeManagerUrl +"'>" + tr("safe") + "</a>" +
                       tr("using qr code login") +
                       "<a href='" + knowMoreUrl +  "'>" + tr("know more") + "</a>");
    cancelButton->setText(tr("Cancel"));
}

void SafeLoginWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(":/safe/safe_big_bkg"));
}
