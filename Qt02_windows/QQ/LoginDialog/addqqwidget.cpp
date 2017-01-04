#include "addqqwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

AddQQWidget::AddQQWidget(QWidget *parent) :
    QWidget(parent)
{
    if(parent)
        this->setFixedSize(parent->size());

    createUI();
    setUILayout();
    setConnect();

    retranslateUI();
}

void AddQQWidget::createUI()
{
    addQQButton = new PushButton(":/button/add_qq_button_normal",
                                 ":/button/add_qq_button_hover",
                                 ":/button/add_qq_button_pressed");
    addQQButton->setObjectName("addQQButton");//设置对象名后，在QSS中才能使用QPushButton#addQQButton进行配置
    addQQButton->setFixedSize(130, 42);

    singleAccountLoginButton = new PushButton(":/button/single_account_button_mormal",
                                              ":/button/single_account_button_hover",
                                              ":/button/single_account_button_pressed");
    singleAccountLoginButton->setObjectName("singleAccountLoginButton");

    loginButton = new PushButton(":/button/login_button_normal",
                                 ":/button/login_button_hover",
                                 ":/button/login_button_pressed");
    loginButton->setObjectName("loginButton");

    qrCodeLoginButton = new PushButton(":/button/qr_code_normal",
                                       ":/button/qr_code_hover",
                                       ":/button/qr_code_pressed");
    qrCodeLoginButton->setObjectName("qrCodeLoginButton");
}

void AddQQWidget::setUILayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(addQQButton, 0, Qt::AlignVCenter | Qt::AlignHCenter);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(singleAccountLoginButton, 0, Qt::AlignVCenter | Qt::AlignLeft);
    hLayout->addWidget(loginButton, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    hLayout->addWidget(qrCodeLoginButton, 0, Qt::AlignVCenter | Qt::AlignRight);
    hLayout->setContentsMargins(12, 0, 5, 5);

    layout->addStretch();
    layout->addLayout(hLayout);
    layout->setContentsMargins(0, 120, 0, 0);

    this->setLayout(layout);
}

void AddQQWidget::setConnect()
{
    connect(singleAccountLoginButton, &PushButton::clicked, this, &AddQQWidget::singleAccountLogin_clicked);
    connect(addQQButton, &PushButton::clicked, this, &AddQQWidget::multiAccountLogin_clicked);
    connect(qrCodeLoginButton, &PushButton::clicked, this, &AddQQWidget::qrCode_clicked);
}

void AddQQWidget::retranslateUI()
{
    addQQButton->setText(tr("Add Account"));
    loginButton->setText(tr("Login"));
}
