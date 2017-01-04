#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T19:02:55
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webqq21
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tools.cpp \
    httpmethod.cpp \
    verifylabel.cpp \
    mylineedit.cpp \
    myjson.cpp \
    maindockwidget.cpp \
    globalset.cpp \
    chatbox_dockwidget.cpp \
    poll2thread.cpp \
    pop_dockwidget.cpp \
    webqq.cpp \
    mycookiejar.cpp

HEADERS  += widget.h \
    tools.h \
    httpmethod.h \
    verifylabel.h \
    mylineedit.h \
    myjson.h \
    maindockwidget.h \
    globalset.h \
    globalstruct.h \
    chatbox_dockwidget.h \
    poll2thread.h \
    pop_dockwidget.h \
    webqq.h \
    mycookiejar.h

FORMS    += widget.ui \
    maindockwidget.ui \
    chatbox_dockwidget.ui \
    pop_dockwidget.ui
