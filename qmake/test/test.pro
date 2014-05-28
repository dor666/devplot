TEMPLATE = app
CONFIG += c++11
#CONFIG -= app_bundle

QT       += core gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEST_DIR = ../../test
TEST_SRC_DIR = $$TEST_DIR/src
SOURCES += $$TEST_SRC_DIR/main.cpp \
    ../../test/src/gui_fixture.cpp \
    ../../test/src/serial_device-test.cpp

HEADERS += \
    ../../test/src/gui_fixture.h \
    #../../test/src/serial_device_mock.h \
    main-test.h


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

## gmock

GMOCK_DIR += $$TEST_DIR/deps/gmock
INCLUDEPATH += $$GMOCK_DIR/include
INCLUDEPATH += $$GMOCK_DIR/
SOURCES += $$GMOCK_DIR/src/gmock-all.cc

GTEST_DIR = $$GMOCK_DIR/gtest
INCLUDEPATH += $$GTEST_DIR/include
INCLUDEPATH += $$GTEST_DIR
SOURCES += $$GTEST_DIR/src/gtest-all.cc

LIBS += -lpthread ## todo check it on non-unix platforms

##suppress gmock warnings
QMAKE_CXXFLAGS += -Wno-missing-field-initializers -Wno-write-strings

# Run all test after linking
QMAKE_POST_LINK += ./$$TARGET

