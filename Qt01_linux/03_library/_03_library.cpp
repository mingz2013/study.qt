#include "_03_library.h"


_03_library::_03_library()
{
}

const char * _03_library::getHelloWorld()
{
    return "Hello World";
}

int getSquare(int nParam)
{
    return (nParam* nParam);
}
