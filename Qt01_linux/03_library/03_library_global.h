#ifndef 03_LIBRARY_GLOBAL_H
#define 03_LIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(03_LIBRARY_LIBRARY)
#  define 03_LIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define 03_LIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // 03_LIBRARY_GLOBAL_H
