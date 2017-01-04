#ifndef POLL2THREAD_H
#define POLL2THREAD_H

#include <QThread>

class poll2Thread : public QThread
{
    Q_OBJECT
public:
    explicit poll2Thread(QObject *parent = 0);
    void stop();    // 停止线程

protected:
    void run();

private:
    bool quit ;
    
};

#endif // POLL2THREAD_H
