
#include "gui_fixture.h"
#include "serial_device_mock.h"
#include "../devplot-lib/ui_serial_device.h"

using namespace ::dplot::test;
using namespace ::dplot;
using ::testing::Return;

TEST_F(GuiTest, App_launch) {

}

TEST_F(WindowlessWidgetTest, device_creation_will_enumerate_ports)
{
    SerialPortFactory_Mock factoryMock;

    QStringList fakePorts;
    fakePorts << "COM1" << "COM66";

    EXPECT_CALL(factoryMock, EnumeratePorts()).WillOnce(Return(fakePorts));

    SerialDevice device(&factoryMock, nullptr);

    EXPECT_STREQ("Disconnect", device.Test_GetUi()->portComboBox->itemText(0).toLatin1());
    EXPECT_STREQ("COM1", device.Test_GetUi()->portComboBox->itemText(1).toLatin1());
    EXPECT_STREQ("COM66", device.Test_GetUi()->portComboBox->itemText(2).toLatin1());
}
