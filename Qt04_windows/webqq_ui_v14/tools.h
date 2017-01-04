#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QRect>

/**
 *工具类
**/
class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = 0);
    static QString getRand(const int n); // 取n位随机数
    static int getRand(const int a,const int b); // 取[a.b)之间的随机数
    static QString getMidOfTwoText( const QString &context, const QString &left, const QString &right);// 取两文本中间
    static QString getCurrentTimeStamp();    // 获取时间戳
    static QString getTimeNow();        // 获取格式化的当前时间
    static QRect getDesktopRect();      // 获取屏幕 rect
    
};

#endif // TOOLS_H
