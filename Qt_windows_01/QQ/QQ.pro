#-------------------------------------------------
#
# Project created by QtCreator 2013-09-02T13:55:42
# zdd/zddmail@gmail.com
# Just for Fun.
# 所有图片资料来自腾讯QQ,请勿商用。
# 2013年9月5日13:36:32
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQ
TEMPLATE = app

CONFIG += qaxcontainer

SOURCES += main.cpp \
    LoginDialog/systemtray.cpp \
    LoginDialog/logindialog.cpp \
    LoginDialog/backgroundwidget.cpp \
    LoginDialog/imagewidget.cpp \
    LoginDialog/picturescrollwidget.cpp \
    LoginDialog/backgroundfactory.cpp \
    LoginDialog/pseudoflashwidget.cpp \
    LoginDialog/addqqwidget.cpp \
    LoginDialog/pushbutton.cpp \
    LoginDialog/loginwidget.cpp \
    LoginDialog/headwidget.cpp \
    LoginDialog/multiaccountloginwidget.cpp \
    LoginDialog/safeloginwidget.cpp \
    LoginDialog/flashwidget.cpp \
    LoginDialog/toolwidget.cpp

HEADERS  += \
    LoginDialog/systemtray.h \
    LoginDialog/logindialog.h \
    LoginDialog/backgroundwidget.h \
    LoginDialog/imagewidget.h \
    LoginDialog/picturescrollwidget.h \
    LoginDialog/backgroundfactory.h \
    LoginDialog/pseudoflashwidget.h \
    LoginDialog/addqqwidget.h \
    LoginDialog/pushbutton.h \
    LoginDialog/loginwidget.h \
    LoginDialog/headwidget.h \
    LoginDialog/multiaccountloginwidget.h \
    LoginDialog/safeloginwidget.h \
    LoginDialog/flashwidget.h \
    LoginDialog/toolwidget.h


TRANSLATIONS += QQ_zh.ts QQ_en.ts

OTHER_FILES += \
    Resources/Qss/logindialog.qss

RESOURCES += \
    logindialog.qrc

RC_FILE = qq.rc
