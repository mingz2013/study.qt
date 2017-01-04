#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#define MAX_INFO_LENGTH 1024

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;
    {
        QHBoxLayout *vLayout = new QHBoxLayout;
        vLayout->addWidget(new QLabel(tr("请输入用户的意见（不超过50个汉字）：")));
        //vLayout->addWidget(new QLineEdit);
        layout->addLayout(vLayout);
        m_QtextEdit = new QTextEdit;
        layout->addWidget(m_QtextEdit);
    }

    layout->addSpacing(10);
    {
        QHBoxLayout *vLayout = new QHBoxLayout;
        vLayout->addWidget(new QLabel(tr("请输入用户的留言：")));
        m_QLineEdit_LeaveWord = new QLineEdit;
        vLayout->addWidget(m_QLineEdit_LeaveWord);
        layout->addLayout(vLayout);

    }

    {
        m_QtextEdit_LeaveWord = new QTextEdit;
        m_QtextEdit_LeaveWord->setAcceptRichText(true);
        layout->addWidget(m_QtextEdit_LeaveWord);
    }

    /*这里修改了*/
    //setLayout(layout);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    this->setCentralWidget(widget);

    connect(m_QtextEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentHasModified()));
    connect(m_QLineEdit_LeaveWord, SIGNAL(textChanged(const QString&)),
            this, SLOT(documentHasModified_LeaveWord(const QString&)));
    this->setGeometry(50, 50, 800, 600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::documentHasModified()
{
    if (this->m_QtextEdit->document()->toPlainText().size() > MAX_INFO_LENGTH) {
        QString tmp = m_QtextEdit->document()->toPlainText().left(MAX_INFO_LENGTH);
        m_QtextEdit->clear();
        m_QtextEdit->insertPlainText(tmp);
    }
}

void MainWindow::documentHasModified_LeaveWord(const QString & text)
{
    QString qstrRichText(tr("%1%2%1").arg("<img src=\"Qt.png\">").arg(text));
    m_QtextEdit_LeaveWord->setText(qstrRichText);
}
