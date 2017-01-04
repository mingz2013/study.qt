#include "tools.h"

using namespace std;

Tools::Tools(QObject *parent) :
    QObject(parent)
{
}

/**
 *函数名：getRand
 *  参数1：int类型
 *  返回值：Qstring类型
 *  作用：取n位随机数
**/
QString Tools::getRand(const int n)
{
    // 方法1，效果好
    QTime t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    // 方法2，效果不好，连续取的时候有相同的时候
    //qsrand(time(NULL));

    QString result = NULL;
    int r = 0;
    QString str = NULL;
    for(int i = 0; i < n; i++)
    {
        //r = qrand() % (b - a) + a;  // 取[a, b)之间的随机数
        r = qrand();
        str.setNum(r);
        result += str.right(1);

    }
    return result;
}

/**
 *函数名：getRand
 *  参数1：int类型
 *  参数2：int类型
 *  返回值：int类型
 *  作用：生成[a,b)之间的随机数
**/
int Tools::getRand(const int a, const int b)
{
    // 方法1，效果好
    QTime t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    return qrand() % (b - a) + a;  // 取[a, b)之间的随机数
}

/**
 *函数名：getMidOfTwoText
 *  参数1：初始字串
 *  参数2：左边的字串
 *  参数3：右边的字串
 *  返回值：QString
 *  作用：从前往后查找left，从后往前查找right，返回两文本中间字串
**/
QString Tools::getMidOfTwoText(const QString &context, const QString &left, const QString &right)
{
    //str123str456str789
    //qDebug() << context.lastIndexOf("str");   // 返回起始位置，从最后往前寻找
    //qDebug() << context.indexOf("str");       // 返回字串起始位置，从前往后找
    return context.mid(
                context.indexOf(left) + left.length(),
                context.lastIndexOf(right) - (context.indexOf(left) + left.length())
                );

}

/**
 *取时间戳
**/
QString Tools::getCurrentTimeStamp()
{
    //QDateTime tt;
    //QTime time;
    //qDebug()<<time.currentTime();
    //tt.setTime(time.currentTime());
    //qDebug()<<tt.toTime_t();
    QString str = QString::number(QDateTime::currentMSecsSinceEpoch());

    qDebug() << str;
    return str;

}

/**
 *获取格式化的当前时间
**/
QString Tools::getTimeNow()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    return str;
}



