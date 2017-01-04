#ifndef PICTURESCROLLWIDGET_H
#define PICTURESCROLLWIDGET_H

#include "backgroundwidget.h"
#include <QUrl>

class PictureScrollWidget : public BackgroundWidget
{
    Q_OBJECT
public:
    explicit PictureScrollWidget(const QString &pictureScrollPath, const QString &url, QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
private:
    QUrl pictureScrollUrl;
    QPixmap pixmap;
    QPixmap texturePixmap;
};

#endif // PICTURESCROLLWIDGET_H
