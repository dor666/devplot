#-------------------------------------------------
#
# Project created by QtCreator 2014-05-25T11:06:23
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = devplot-app
TEMPLATE = app

CONFIG += c++11

SRC_DIR = ../../src
SOURCES += $$SRC_DIR/main.cpp

## devplot-lib
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../devplot-lib/release/ -ldevplot-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../devplot-lib/debug/ -ldevplot-lib
else:unix: LIBS += -L$$OUT_PWD/../devplot-lib/ -ldevplot-lib

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../devplot-lib/release/libdevplot-lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../devplot-lib/debug/libdevplot-lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../devplot-lib/release/devplot-lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../devplot-lib/debug/devplot-lib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../devplot-lib/libdevplot-lib.a
