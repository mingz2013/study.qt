#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "backgroundwidget.h"

class ImageWidget : public BackgroundWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(const QString &imagePath, QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap pixmap;
    QPixmap texturePixmap;
};

#endif // IMAGEWIDGET_H
