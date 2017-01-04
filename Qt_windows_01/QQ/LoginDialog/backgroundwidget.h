#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QWidget>

/**
 * @brief The BackgroundWidget class
 * 背景层接口
 */
class BackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundWidget(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    virtual void paintEvent(QPaintEvent *) = 0;
};

#endif // BACKGROUNDWIDGET_H
