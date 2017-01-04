#-------------------------------------------------
#
# Project created by QtCreator 2013-08-05T06:33:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_25_MainWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    maindockwidget.cpp

HEADERS  += widget.h \
    maindockwidget.h \
    Init.h

FORMS    += widget.ui \
    maindockwidget.ui
