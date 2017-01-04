#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = 0);
    void print();
    
};

#endif // MAINCLASS_H
