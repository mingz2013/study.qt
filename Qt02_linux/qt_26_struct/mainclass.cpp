#include "mainclass.h"
#include "test.h"
#include <QDebug>
extern int i;
extern Test ptest;
MainClass::MainClass(QObject *parent) :
    QObject(parent)
{
  //  ptest->a = 12;
   // ptest->b = 13;
    i = 12;
    ptest.a = 12;
    ptest.b = 13;
}

void MainClass::print()
{
    qDebug() << i;
    qDebug() << ptest.a + ptest.b;
}
