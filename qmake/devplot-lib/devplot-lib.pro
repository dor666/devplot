#-------------------------------------------------
#
# Project created by QtCreator 2014-05-25T11:14:05
#
#-------------------------------------------------

TARGET = devplot-lib
TEMPLATE = lib
CONFIG += staticlib c++11

QT += \
        widgets \
        serialport \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

VPATH += ../../src

SOURCES += \
        mainwindow.cpp \
    ../../src/serial_device.cpp

HEADERS  += mainwindow.h \
    ../../src/serial_device.h

FORMS    += mainwindow.ui \
    ../../src/serial_device.ui
