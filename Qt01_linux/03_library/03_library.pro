#-------------------------------------------------
#
# Project created by QtCreator 2013-07-01T20:25:33
#
#-------------------------------------------------

QT       -= gui

TARGET = 03_library
TEMPLATE = lib

DEFINES += 03_LIBRARY_LIBRARY

SOURCES += _03_library.cpp

HEADERS += _03_library.h\
        03_library_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
