#-------------------------------------------------
#
# Project created by QtCreator 2013-08-02T08:29:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_15_JS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \


FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/lib/ -lv8

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

OTHER_FILES += \
    helloworld.js
