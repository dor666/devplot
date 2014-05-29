#include "gui_fixture.h"

using ::testing::Return;

namespace dplot
{
namespace test
{

void GuiTest::SetUp() {

    // Code here will be called immediately after the constructor (right
    // before each test).
    portFactory = new SerialPortFactory_Mock;
    QStringList fakePorts;
    fakePorts << "COM1" << "COM66";
    EXPECT_CALL(*portFactory, EnumeratePorts()).WillOnce(Return(fakePorts));
    mainWindow = new MainWindow(portFactory);
}

void GuiTest::TearDown() {
    app->processEvents();
    delete mainWindow;
    delete portFactory;
    app->processEvents();
}

} //namespace test
} //namespace dplot
