#-------------------------------------------------
#
# Project created by QtCreator 2013-08-02T12:57:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_19_JS_CLASS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    v8_js.cpp

HEADERS  += mainwindow.h \
    v8_js.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/lib/ -lv8

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
