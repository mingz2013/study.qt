#include "headwidget.h"

#include <QHBoxLayout>
#include <QPainter>

HeadWidget::HeadWidget(const QString &head, QWidget *parent) :
    QWidget(parent)
{
    backgroundPixmap = QPixmap(":/head/head_background").copy(5, 5, 82, 82);
    this->setFixedSize(82, 82);

    headPixmap.load(head);

    statusButton = new QPushButton(QIcon(":/status/imonline"), "");
    statusButton->setObjectName("statusButton");
    statusButton->setFixedSize(16, 16);

    statusButton->setMenu(createMenu());

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(statusButton, 0, Qt::AlignRight | Qt::AlignBottom);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    retranslateUI();
}

QMenu* HeadWidget::createMenu()
{
    QMenu *menu = new QMenu(this);

    imonline = new QAction(menu);
    imonline->setIcon(QIcon(":/status/imonline"));
    menu->addAction(imonline);

    qme = new QAction(menu);
    qme->setIcon(QIcon(":/status/qme"));
    menu->addAction(qme);

    menu->addSeparator();

    away = new QAction(menu);
    away->setIcon(QIcon(":/status/away"));
    menu->addAction(away);

    busy = new QAction(menu);
    busy->setIcon(QIcon(":/status/busy"));
    menu->addAction(busy);

    mute = new QAction(menu);
    mute->setIcon(QIcon(":/status/mute"));
    menu->addAction(mute);

    menu->addSeparator();

    invisible = new QAction(menu);
    invisible->setIcon(QIcon(":/status/invisible"));
    menu->addAction(invisible);

    return menu;
}

void HeadWidget::retranslateUI()
{
    imonline->setText(tr("imonline"));
    qme->setText(tr("Qme"));
    away->setText(tr("away"));
    busy->setText(tr("busy"));
    mute->setText(tr("mute"));
    invisible->setText(tr("invisible"));
}

void HeadWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(1, 1, 80, 80), headPixmap);
    painter.drawPixmap(this->rect(), backgroundPixmap);
}
