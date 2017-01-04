#ifndef FLASHWIDGET_H
#define FLASHWIDGET_H

#include <QAxWidget>
#include <QWidget>
#include <QTimer>

#include "backgroundwidget.h"

/**
 * @brief The FlashWidget class
 * @zdd/zddmail@gmail.com
 * 使用QAxWidget插件实现Flash(.swf)播放，
 * 当该控件被透明Widget遮挡后，变黑，未用。
 */
class FlashWidget : public BackgroundWidget
{
    Q_OBJECT
public:
    explicit FlashWidget(QString flashPath, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
signals:
    void OnReadyStateChange(int);
public slots:
    void update();
private:
    QAxWidget *flash;
    QTimer *timer;
};

#endif // FLASHWIDGET_H
