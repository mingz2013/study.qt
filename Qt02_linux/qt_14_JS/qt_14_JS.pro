SOURCES += \
    helloworld.cpp

unix:!macx: LIBS += -L$$PWD/lib/ -lv8

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
