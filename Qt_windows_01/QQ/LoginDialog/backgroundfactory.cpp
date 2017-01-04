#include "backgroundfactory.h"

#include "imagewidget.h"
#include "picturescrollwidget.h"
#include "pseudoflashwidget.h"
#include "flashwidget.h"

#include <QTime>

BackgroundFactory::BackgroundFactory(const BackgroundType &backgroundType, QObject *parent) :
    QObject(parent)
{
    bt = backgroundType;
}

//以下函数的内容将从配置文件读得
QString BackgroundFactory::getPseudoFlashDir()
{
    switch(timeInterval)
    {
    case Morning:
        return "Resources/LoginUI/background/morning";
        break;
    case Noon:
        return "Resources/LoginUI/background/noon";
        break;
    case Afternoon:
        return "Resources/LoginUI/background/afternoon";
        break;
    case Night:
        return "Resources/LoginUI/background/night";
        break;
    }
    return "";
}

QString BackgroundFactory::getImagePath()
{
    switch(timeInterval)
    {
    case Morning:
        return ":/background/morning";
        break;
    case Noon:
        return ":/background/noon";
        break;
    case Afternoon:
        return ":/background/afternoon";
        break;
    case Night:
        return ":/background/night";
        break;
    }
    return "";
}

QString BackgroundFactory::getFlashPath()
{
    switch(timeInterval)
    {
    case Morning:
        return ":/background/morning.swf";
        break;
    case Noon:
        return ":/background/noon.swf";
        break;
    case Afternoon:
        return ":/background/afternoon.swf";
        break;
    case Night:
        return ":/background/night.swf";
        break;
    }
    return "";
}

void BackgroundFactory::getPictureScrollInfo(QString &path, QString &url)
{
    path = ":/background/picturescroll";
    url = "http://im.qq.com/culture/china/";
}

BackgroundWidget* BackgroundFactory::createBackground(QWidget *widget)
{
    BackgroundWidget *bw;

    setTimeInterval();

    QString path, url;
    switch(bt)
    {
    case PictureScroll:
        getPictureScrollInfo(path, url);
        bw = new PictureScrollWidget(path, url, widget);
        break;
    case Flash:
        bw = new PseudoFlashWidget(getPseudoFlashDir(), widget);
        //bw = new FlashWidget(getFlashPath(), widget);
        break;
    case Image:
        bw = new ImageWidget(getImagePath(), widget);
    default:
        ;
    }

    return bw;
}

void BackgroundFactory::setTimeInterval()
{
    QTime time = QTime::currentTime();
    int hour = time.hour();

    if(hour >= 6 && hour < 9)
    {
        timeInterval = Morning;
    }
    else if(hour >= 9 && hour < 17)
    {
        timeInterval = Noon;
    }
    else if(hour >= 17 && hour < 20)
    {
        timeInterval = Afternoon;
    }
    else
    {
        timeInterval = Night;
    }
}
