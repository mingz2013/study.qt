#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T19:02:55
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GroupMsg_V0.6
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tools.cpp \
    httpmethod.cpp \
    verifylabel.cpp \
    mylineedit.cpp \
    v8_js.cpp \
    myjson.cpp \
    globalset.cpp \
    poll2thread.cpp

HEADERS  += widget.h \
    tools.h \
    httpmethod.h \
    verifylabel.h \
    mylineedit.h \
    v8_js.h \
    myjson.h \
    globalset.h \
    globalstruct.h \
    poll2thread.h

FORMS    += widget.ui






unix|win32: LIBS += -L$$PWD/lib/ -lv8

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include


