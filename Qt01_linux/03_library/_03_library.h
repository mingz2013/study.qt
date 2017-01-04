#ifndef _03_LIBRARY_H
#define _03_LIBRARY_H

#include "03_library_global.h"

class 03_LIBRARYSHARED_EXPORT _03_library
{
    
public:
    _03_library();
    // 共享库提供的公共成员函数
    const char* getHelloWorld();
};

// 共享库提供的标准c风格函数
extern "C" 03_LIBRARYSHARED_EXPORT int getSquare(int nParam);

#endif // _03_LIBRARY_H
