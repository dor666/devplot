
#include "gui_fixture.h"
#include "serial_device_mock.h"
#include "../devplot-lib/ui_serial_device.h"

using namespace ::dplot::test;
using namespace ::dplot;
using ::testing::Return;

void PrintTo(const QString& str, ::std::ostream* os)
{
    *os << "QString(" << str.toStdString() << ")";
}

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

void CompareComboBoxLabels(
        QStringList listExpected, const QString expectedSelected,
        const QComboBox* comboBox, std::string where)
{
    for(int i = 0; i < listExpected.length(); ++i)
    {
        EXPECT_EQ(listExpected[i], comboBox->itemText(i)) << " called at: " << where;
    }
    EXPECT_EQ(expectedSelected, comboBox->currentText());
}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

TEST_F(WindowlessWidgetTest, default_connection_values)
{
    SerialPortFactory_Mock factoryMock;
    QStringList fakePorts;
    EXPECT_CALL(factoryMock, EnumeratePorts()).WillOnce(Return(fakePorts));

    SerialDevice device(&factoryMock, nullptr);

    auto gui = device.Test_GetUi();


    EXPECT_EQ(115200, gui->baudRateSpinBox->value());

    EXPECT_STREQ("Disconnect", gui->portComboBox->currentText().toLatin1());

    CompareComboBoxLabels({"5", "6", "7", "8"},
                          "8",
                gui->dataBitsComboBox, AT);

    CompareComboBoxLabels({"None", "Even", "Odd", "Space", "Mark"},
                          "None",
                gui->parityComboBox, AT);

    CompareComboBoxLabels({"1", "1.5", "2"},
                          "1",
                gui->stopBitsComboBox, AT);

    CompareComboBoxLabels({"None", "Hardware", "Software"},
                          "None",
                gui->flowControlComboBox, AT);

    EXPECT_STREQ("Disconnected", gui->statusDisplayLabel->text().toLatin1());
}
