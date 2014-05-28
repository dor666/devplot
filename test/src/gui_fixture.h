#include "mainwindow.h"
#include "gtest/gtest.h"
#include "main-test.h"

#include <QApplication>

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

    GuiTest() {
        // You can do set-up work for each test here.
    }

    virtual ~GuiTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        mainWindow = new MainWindow();
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).

        app->processEvents();
        delete mainWindow;
        app->processEvents();
    }

    // Objects declared here can be used by all tests in the test case for Foo.
};

} //namespace test
} //namespace dplot
