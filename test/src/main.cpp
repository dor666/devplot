#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "main-test.h"

namespace dplot
{
namespace test {
QApplication* app;
}
}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.

    using namespace ::dplot;
    using namespace ::dplot::test;


    ///@see app
    int fakeArgc = 0;
    app = new QApplication(fakeArgc, (char **)NULL);
    app->setQuitOnLastWindowClosed(false);

    ::testing::InitGoogleMock(&argc, argv);

    int ret = RUN_ALL_TESTS();
    delete app;
    return ret;
}
