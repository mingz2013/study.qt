#include "poll2thread.h"
#include <QDebug>
#include "globalset.h"

extern GlobalSet globalset;// 引用全局变量

poll2Thread::poll2Thread(QWidget *parent) :
    QThread(parent)
{

    quit = false;
}

void poll2Thread::run()
{
    while(!quit){
        //post_poll2();
        globalset.webqq->post_poll2();
        sleep(5);
    }

}

void poll2Thread::stop()
{
    quit = true;
}



