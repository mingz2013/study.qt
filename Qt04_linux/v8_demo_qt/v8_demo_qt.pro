#-------------------------------------------------
#
# Project created by QtCreator 2013-08-31T13:31:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v8_demo_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

#ws2_32.lib
#winmm.lib
#LIBS += -lws2_32
#LIBS += -lwinmm







unix|win32: LIBS += -L$$PWD/lib/ -lv8

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
