#include "multiaccountloginwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

MultiAccountLoginWidget::MultiAccountLoginWidget(QWidget *parent) :
    QWidget(parent)
{
    if(parent)
        this->setFixedSize(parent->size());

    createUI();
    setUILayout();
    setConnect();

    retranslateUI();
}

void MultiAccountLoginWidget::setConnect()
{
    connect(sureAddButton, &PushButton::clicked, this, &MultiAccountLoginWidget::sureAdd_clicked);
    connect(cancelButton, &PushButton::clicked, this, &MultiAccountLoginWidget::cancel_clicked);
}

void MultiAccountLoginWidget::createUI()
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

    sureAddButton = new PushButton(":/button/login_button_normal",
                                   ":/button/login_button_hover",
                                   ":/button/login_button_pressed");
    sureAddButton->setFixedSize(80, 26);

    cancelButton= new PushButton(":/button/login_button_normal",
                                 ":/button/login_button_hover",
                                 ":/button/login_button_pressed");
    cancelButton->setFixedSize(80, 26);
}

void MultiAccountLoginWidget::setUILayout()
{
    keyboardButton->setGeometry(190 - keyboardButton->width(), 1,
                                keyboardButton->width(), keyboardButton->height());

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(new QLabel(""));//占位
    btnLayout->addWidget(sureAddButton);
    btnLayout->addWidget(cancelButton, 0, Qt::AlignRight);
    btnLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(usernameComboBox);
    vLayout->addWidget(passwordLineEdit);
    vLayout->addLayout(btnLayout);
    vLayout->setContentsMargins(10, 0, 10, 0);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(headWidget);
    layout->addLayout(vLayout);
    layout->setContentsMargins(40, 140, 30, 55);

    this->setLayout(layout);
}

void MultiAccountLoginWidget::retranslateUI()
{
    initUsernameText = tr("QQ/Phone/Email");
    initPasswordText = tr("password");

    usernameComboBox->lineEdit()->setText(initUsernameText);
    passwordLineEdit->setText(initPasswordText);

    sureAddButton->setText(tr("OK"));
    cancelButton->setText(tr("Cancel"));
}
