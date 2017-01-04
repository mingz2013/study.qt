#ifndef PSEUDOFLASHWIDGET_H
#define PSEUDOFLASHWIDGET_H

#include "backgroundwidget.h"

#include <QTimer>
#include <QPixmap>
#include <QVector>

class PseudoFlashWidget : public BackgroundWidget
{
    Q_OBJECT
public:
    explicit PseudoFlashWidget(const QString &dirPath, QWidget *parent = 0);
    
signals:
    
public slots:
    void setNext();

protected:
    void paintEvent(QPaintEvent *);
private:
    QTimer *timer;
    QVector<QPixmap> pixmaps;
    int index;

    QPixmap texturePixmap;
};

#endif // PSEUDOFLASHWIDGET_H
