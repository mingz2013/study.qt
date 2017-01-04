#ifndef POLL2THREAD_H
#define POLL2THREAD_H

#include <QThread>
#include "globalset.h"

extern GlobalSet globalset;// 引用全局变量

class poll2Thread : public QThread
{
    Q_OBJECT
public:
    explicit poll2Thread(QWidget *parent = 0);
    void stop();    // 停止线程
    
protected:
    void run();


    
public slots:

private:

    bool quit ;
    
};

#endif // POLL2THREAD_H
