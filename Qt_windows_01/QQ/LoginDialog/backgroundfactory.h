#ifndef BACKGROUNDFACTORY_H
#define BACKGROUNDFACTORY_H

#include <QObject>
#include "backgroundwidget.h"

/**
 * @brief The BackgroundFactory class
 * 背景工厂类，根据参数创建不同的背景层
 */
class BackgroundFactory : public QObject
{
    Q_OBJECT
public:
    enum BackgroundType {
        Flash,
        PictureScroll,
        Image
    };

public:
    explicit BackgroundFactory(const BackgroundType &backgroundType = Image,
                               QObject *parent = 0);
    BackgroundWidget* createBackground(QWidget *widget = 0);

private:
    BackgroundType bt;
private:
    enum TimeInterval {
        Morning,
        Noon,
        Afternoon,
        Night
    };
    TimeInterval timeInterval;

    void setTimeInterval();
private:
    QString getImagePath();
    QString getFlashPath();
    QString getPseudoFlashDir();
    void getPictureScrollInfo(QString &path, QString &url);
};

#endif // BACKGROUNDFACTORY_H
