#-------------------------------------------------
#
# Project created by QtCreator 2013-07-31T18:38:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_13_jsoncpp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    json/json_writer.cpp \
    json/json_valueiterator.inl \
    json/json_value.cpp \
    json/json_reader.cpp \
    json/json_internalmap.inl \
    json/json_internalarray.inl

HEADERS  += mainwindow.h \
    json/writer.h \
    json/value.h \
    json/reader.h \
    json/json_batchallocator.h \
    json/json.h \
    json/forwards.h \
    json/features.h \
    json/config.h \
    json/autolink.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    json/sconscript
