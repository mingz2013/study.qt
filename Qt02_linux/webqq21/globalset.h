#ifndef GLOBALSET_H
#define GLOBALSET_H

#include <QObject>
#include "globalstruct.h"
#include "webqq.h"

/**
 *类名称：Globalset
 *作用：用来担当全局变量，类之间传递数据
**/

class GlobalSet : public QObject
{
    Q_OBJECT
public:

    OTHER other_struct;
    webQQ *webqq = new webQQ(this);
};

#endif // GLOBALSET_H
