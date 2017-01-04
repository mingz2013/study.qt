#include "loginwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    if(parent)
        this->setFixedSize(parent->size());

    createUI();
    setUILayout();
    setConnect();

    retranslateUI();
}

void LoginWidget::setConnect()
{
    connect(multiAccountLoginButton, &PushButton::clicked, this, &LoginWidget::multiAccount_clicked);
    connect(loginButton, &PushButton::clicked, this, &LoginWidget::login_clicked);
    connect(qrCodeLoginButton, &PushButton::clicked, this, &LoginWidget::qrCode_clicked);
}

void LoginWidget::createUI()
{
    headWidget = new HeadWidget(":/head/default_head");

    usernameComboBox = new QComboBox;
    usernameComboBox->setObjectName("username");
    //usernameComboBox->setFixedSize(160, 22);
    usernameComboBox->setEditable(true);
    usernameComboBox->lineEdit()->setMaxLength(40);
    usernameComboBox->setContextMenuPolicy(Qt::NoContextMenu);

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setObjectName("password");
    //passwordLineEdit->setFixedSize(160, 22);
    //passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMaxLength(16);
    passwordLineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    keyboardButton = new PushButton(":/button/keyboard", passwordLineEdit);
    keyboardButton->setCursor(Qt::PointingHandCursor);

    rememberPasswordCheckBox = new QCheckBox;
    autoLoginCheckBox = new QCheckBox;

    registerButton = new PushButton(":/button/zhuce",
                                    ":/button/zhuce_hover",
                                    ":/button/zhuce_pressed");
    registerButton->setCursor(Qt::PointingHandCursor);

    findBackPasswordButton = new PushButton(":/button/mima",
                                            ":/button/mima_hover",
                                            ":/button/mima_pressed");
    findBackPasswordButton->setCursor(Qt::PointingHandCursor);

    multiAccountLoginButton = new PushButton(":/button/multi_account_button_normal",
                                              ":/button/multi_account_button_hover",
                                              ":/button/multi_account_button_pressed");
    multiAccountLoginButton->setObjectName("multiAccountLoginButton");

    loginButton = new PushButton(":/button/login_button_normal",
                                 ":/button/login_button_hover",
                                 ":/button/login_button_pressed");
    loginButton->setObjectName("loginButton");

    qrCodeLoginButton = new PushButton(":/button/qr_code_normal",
                                       ":/button/qr_code_hover",
                                       ":/button/qr_code_pressed");
    qrCodeLoginButton->setObjectName("qrCodeLoginButton");
}

void LoginWidget::setUILayout()
{
    keyboardButton->setGeometry(190 - keyboardButton->width(), 1,
                                keyboardButton->width(), keyboardButton->height());

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(rememberPasswordCheckBox);
    hLayout1->addWidget(autoLoginCheckBox);
    hLayout1->addWidget(new QLabel(), 0, Qt::AlignRight);//占位
    hLayout1->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(usernameComboBox);
    vLayout1->addWidget(passwordLineEdit);
    vLayout1->addLayout(hLayout1);
    vLayout1->setContentsMargins(0, 0, 0, 0);


    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(registerButton);
    vLayout2->addWidget(findBackPasswordButton);
    vLayout2->setContentsMargins(10, 0, 0, 20);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(headWidget, 0, Qt::AlignLeft);
    hLayout2->addLayout(vLayout1);
    hLayout2->addLayout(vLayout2);
    hLayout2->setContentsMargins(18, 0, 15, 15);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(multiAccountLoginButton, 0, Qt::AlignVCenter | Qt::AlignLeft);
    hLayout3->addWidget(loginButton, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    hLayout3->addWidget(qrCodeLoginButton, 0, Qt::AlignVCenter | Qt::AlignRight);
    hLayout3->setContentsMargins(12, 0, 5, 5);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(hLayout2);
    layout->addLayout(hLayout3);
    layout->setContentsMargins(0, 150, 0, 0);

    this->setLayout(layout);

    this->setContentsMargins(0, 0, 0, 0);
}

void LoginWidget::retranslateUI()
{
    initUsernameText = tr("QQ/Phone/Email");
    initPasswordText = tr("password");

    usernameComboBox->lineEdit()->setText(initUsernameText);
    passwordLineEdit->setText(initPasswordText);

    rememberPasswordCheckBox->setText(tr("RememberPwd"));
    autoLoginCheckBox->setText(tr("AutoLogin"));
    loginButton->setText(tr("Login"));
}
