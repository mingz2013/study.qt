#include "mythread.h"
#include <QDebug>
#include <QMutex>

extern int p[10];
extern int i;
extern int a;
extern QMutex mutex;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
}

void MyThread::run()
{
    while(true){

        mutex.lock();
        if(i <= a){
            qDebug() << "MyThread";

            p[i] = i;
            i++;
            if(i == 11)
            {
                i = 0;
            }
        }
        mutex.unlock();
        sleep(2);

    }
}
