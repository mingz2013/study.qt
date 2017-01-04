#include "imagewidget.h"
#include <QPainter>

ImageWidget::ImageWidget(const QString &imagePath, QWidget *parent) :
    BackgroundWidget(parent)
{
    pixmap.load(imagePath);

    if(parent)
    {
        this->setFixedSize(parent->size());
    }
    else
    {
        this->setFixedSize(pixmap.size());
    }

    texturePixmap = QPixmap(":/background/texture").copy(10, 5, 25, this->height());
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
    painter.drawPixmap(this->rect(), texturePixmap);
}
