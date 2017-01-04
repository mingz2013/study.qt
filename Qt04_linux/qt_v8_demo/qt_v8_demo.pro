#-------------------------------------------------
#
# Project created by QtCreator 2013-08-30T15:29:21
#
#-------------------------------------------------

QT       += core gui
QT       += v8-private
QT += core-private v8-private qml-private testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_v8_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    v8_js.cpp

HEADERS  += mainwindow.h \
    v8_js.h

FORMS    += mainwindow.ui
