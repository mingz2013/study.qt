#include "picturescrollwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDesktopServices>

PictureScrollWidget::PictureScrollWidget(const QString &pictureScrollPath, const QString &url, QWidget *parent) :
    BackgroundWidget(parent), pictureScrollUrl(url)
{
    pixmap.load(pictureScrollPath);

    if(parent)
    {
        this->setFixedSize(parent->size());
    }
    else
    {
        this->setFixedSize(pixmap.size());
    }

    texturePixmap = QPixmap(":/background/texture").copy(10, 5, 25, this->height());

    this->setCursor(Qt::PointingHandCursor);
}

void PictureScrollWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
    painter.drawPixmap(this->rect(), texturePixmap);
}

void PictureScrollWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        QDesktopServices::openUrl(pictureScrollUrl);
    }
}
