#ifndef GLOBALSET_H
#define GLOBALSET_H

#include <QObject>
#include "globalstruct.h"

/**
 *类名称：Globalset
 *作用：用来担当全局变量，类之间传递数据
**/

class GlobalSet : public QObject
{
    Q_OBJECT
public:
    COOKIE cookie_struct;
    STRING string_struct;
    OTHER other_struct;
};

#endif // GLOBALSET_H
