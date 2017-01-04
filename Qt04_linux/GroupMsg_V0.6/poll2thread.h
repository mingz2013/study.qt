#ifndef POLL2THREAD_H
#define POLL2THREAD_H

#include <QThread>
#include "httpmethod.h"
#include <QWidget>// 需要加上这条语句

class poll2Thread : public QThread
{
    Q_OBJECT
public:
    explicit poll2Thread(QWidget *parent = 0);
    void stop();    // 停止线程
    
protected:
    void run();

signals:
    void poll2Signal(QString context);
    
public slots:

private:
    httpMethod *httpmethod; // httpMethod类
    bool quit ;

    void post_poll2();
    
};

#endif // POLL2THREAD_H
