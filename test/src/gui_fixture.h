#include "mainwindow.h"
#include "gtest/gtest.h"
#include "main-test.h"

#include <QApplication>

#include "serial_device_mock.h"

namespace dplot {

namespace test
{

class WindowlessWidgetTest : public ::testing::Test {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MainWindow* mainWindow;

    WindowlessWidgetTest() {
        // You can do set-up work for each test here.
    }

    virtual ~WindowlessWidgetTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        app->processEvents();
    }

    // Objects declared here can be used by all tests in the test case for Foo.
};

// The fixture for testing class Foo.
class GuiTest : public ::testing::Test {

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MainWindow* mainWindow;
    SerialPortFactory_Mock* portFactory;

    GuiTest() {
        // You can do set-up work for each test here.
    }

    virtual ~GuiTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    // Objects declared here can be used by all tests in the test case for Foo.
};

} //namespace test
} //namespace dplot
