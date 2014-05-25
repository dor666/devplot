#-------------------------------------------------
#
# Project created by QtCreator 2014-05-25T11:14:05
#
#-------------------------------------------------

TARGET = devplot-lib
TEMPLATE = lib
CONFIG += staticlib

QT += widgets

unix {
    target.path = /usr/lib
    INSTALLS += target
}

VPATH += ../../src

SOURCES += \
        mainwindow.cpp \

HEADERS  += mainwindow.h \

FORMS    += mainwindow.ui \
