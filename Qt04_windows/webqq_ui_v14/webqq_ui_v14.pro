#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T14:34:43
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webQQ
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    maindialog.cpp \
    chatdialog.cpp \
    groupchatdialog.cpp \
    verifylabel.cpp \
    mylineedit.cpp \
    webqq.cpp \
    tools.cpp \
    myjson.cpp \
    mycookiejar.cpp \
    httpmethod.cpp \
    globalset.cpp \
    poll2thread.cpp \
    msgalertdialog.cpp

HEADERS  += logindialog.h \
    maindialog.h \
    chatdialog.h \
    groupchatdialog.h \
    verifylabel.h \
    mylineedit.h \
    webqq.h \
    tools.h \
    myjson.h \
    mycookiejar.h \
    httpmethod.h \
    globalstruct.h \
    globalset.h \
    poll2thread.h \
    msgalertdialog.h

FORMS    += logindialog.ui \
    maindialog.ui \
    chatdialog.ui \
    groupchatdialog.ui \
    MsgAlertDialog.ui \
    msgalertdialog.ui

RESOURCES += \
    logindialog.qrc

RC_FILE = QQ.rc
