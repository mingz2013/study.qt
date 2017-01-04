#-------------------------------------------------
#
# Project created by QtCreator 2013-08-21T19:44:57
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_xml
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myxml.cpp \
    myjson.cpp

HEADERS  += widget.h \
    myxml.h \
    myjson.h

FORMS    += widget.ui
