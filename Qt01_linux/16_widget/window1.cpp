#include "window1.h"
#include "ui_window1.h"

Window1::Window1(QWidget *parent) :
    QWidget(parent)
{
    nickNameLabel = new QLabel("name");
    nickNameEdit = new QLineEdit(this);
    pswdLabel = new QLabel("password");
    pswdEdit = new QLineEdit(this);
    pswdEdit->setEchoMode(QLineEdit::Password);
    accountLabel = new QLabel("account");
    accountEdit = new QLineEdit(this);
    mailLabel = new QLabel("mail");
    mailEdit = new QLineEdit(this);
    introductionLabel = new QLabel("introduct");
    introductionEdit = new QTextEdit(this);
    addressLabel = new QLabel("address");
    addressEdit = new QLineEdit(this);
    jobLabel = new QLabel("job");
    jobEdit = new QLineEdit(this);
    nickNameLayout.addWidget(nickNameLabel);
    nickNameLayout.addWidget(nickNameEdit);
    nickNameLayout.addStretch();
    pswdLayout.addWidget(pswdLabel);
    pswdLayout.addWidget(pswdEdit);
    pswdLayout.addStretch();
    accountLayout.addWidget(accountLabel);
    accountLayout.addWidget(accountEdit);
    accountLayout.addStretch();
    mailLayout.addWidget(mailLabel);
    mailLayout.addWidget(mailEdit);
    mailLayout.addStretch();
    gLayout.addWidget(addressLabel, 0, 0, 1, 1);
    gLayout.addWidget(addressEdit, 0, 1, 1, 1);
    gLayout.addWidget(jobLabel, 1, 0, 1, 1);
    gLayout.addWidget(jobEdit, 1, 1, 1, 1);
    gLayout.addWidget(introductionLabel, 2, 0, 1, 1);
    gLayout.addWidget(introductionEdit, 2, 1, 2, 2);
    hLayout.addLayout(&nickNameLayout);
    hLayout.addLayout(&pswdLayout);
    hLayout1.addLayout(&accountLayout);
    hLayout1.addLayout(&mailLayout);
    vLayout.addLayout(&hLayout, 1);
    vLayout.addLayout(&hLayout1, 1);
    vLayout.addLayout(&gLayout, 1);
    vLayout.addStretch(5);
    setLayout(&vLayout);

}
