#-------------------------------------------------
#
# Project created by QtCreator 2013-07-30T07:24:53
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_10_GET_POST
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    httpmethod.cpp

HEADERS  += mainwindow.h \
    httpmethod.h

FORMS    += mainwindow.ui
