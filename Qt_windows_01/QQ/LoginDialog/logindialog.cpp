#include "logindialog.h"

#include "backgroundfactory.h"
#include <QVBoxLayout>

#include <QApplication>

#include <QPainter>
#include <QBitmap>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(380, 292);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);

    BackgroundFactory factory(BackgroundFactory::Flash);
    backGroundWidget = factory.createBackground(this);

    systemTray = new SystemTray(this, ":/trayicon/offline");

    //注意加入stackedWiget的顺序应和WidgetType一致

    stackedWidget = new QStackedWidget(this);
    stackedWidget->setFixedSize(this->size());

    loginWidget = new LoginWidget(this);
    stackedWidget->addWidget(loginWidget);

    addQQWidget = new AddQQWidget(this);
    stackedWidget->addWidget(addQQWidget);

    multiAccountLoginWidget = new MultiAccountLoginWidget(this);
    stackedWidget->addWidget(multiAccountLoginWidget);

    safeLoginWidget = new SafeLoginWidget(this);
    stackedWidget->addWidget(safeLoginWidget);

    stackedWidget->setCurrentIndex(Login);

    toolWidget = new ToolWidget(this);

    setUILayout();
    setConnect();

    isLeftPressed = false;
}

void LoginDialog::setUILayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(toolWidget, 0, Qt::AlignTop | Qt::AlignRight);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void LoginDialog::setConnect()
{
    connect(loginWidget, &LoginWidget::multiAccount_clicked, this, &LoginDialog::showAddQQWidget);
    connect(loginWidget, &LoginWidget::qrCode_clicked, this, &LoginDialog::showSafeLoginWidget);

    connect(addQQWidget, &AddQQWidget::singleAccountLogin_clicked, this, &LoginDialog::showLoginWidget);
    connect(addQQWidget, &AddQQWidget::multiAccountLogin_clicked, this, &LoginDialog::showMultiAccountLoginWidget);
    connect(addQQWidget, &AddQQWidget::qrCode_clicked, this, &LoginDialog::showSafeLoginWidget);

    connect(multiAccountLoginWidget, &MultiAccountLoginWidget::cancel_clicked, this, &LoginDialog::showAddQQWidget);

    connect(safeLoginWidget, &SafeLoginWidget::cancel_clicked, this, &LoginDialog::showLoginWidget);

    //connect(toolWidget, &ToolWidget::settingButton, )
    connect(toolWidget, &ToolWidget::minimize_clicked, this, &LoginDialog::hide);
    connect(toolWidget, &ToolWidget::close_clicked, &QApplication::quit);//Qt5.1的写法，可以不加接收者，此处加上接收者错误

    //connect(toolWidget, SIGNAL(close_clicked()), qApp, SLOT(quit()));//老版本写法, 正确
    //以下两种方式错误
    //connect(toolWidget, &ToolWidget::close_clicked, qApp, &QApplication::quit);
    //connect(toolWidget, &ToolWidget::close_clicked,
    //qApp, static_cast<void (QApplication::*)()>(&QApplication::quit));
}

void LoginDialog::showLoginWidget()
{
    stackedWidget->setCurrentIndex(Login);
}

void LoginDialog::showAddQQWidget()
{
    stackedWidget->setCurrentIndex(AddQQ);
}

void LoginDialog::showMultiAccountLoginWidget()
{
    stackedWidget->setCurrentIndex(MultiAccountLogin);
}

void LoginDialog::showSafeLoginWidget()
{
    stackedWidget->setCurrentIndex(SafeLogin);
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    //绘制圆角矩形
    QBitmap bitmap(this->size());
    QPainter painter(&bitmap);
    painter.fillRect(bitmap.rect(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.setRenderHint(QPainter::Antialiasing);//平滑
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
    painter.drawRoundedRect(this->rect(), 5, 5);
    this->setMask(bitmap);//可设置不同的形状
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        lastPoint = e->globalPos();
        isLeftPressed = true;
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        this->move(this->pos() + e->globalPos() - lastPoint);
        lastPoint = e->globalPos();
        isLeftPressed = false;
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && isLeftPressed)
    {
        this->move(this->pos() + e->globalPos() - lastPoint);
        lastPoint = e->globalPos();
    }
}
