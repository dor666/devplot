
#include "gui_fixture.h"
#include "serial_device_mock.h"
#include "../devplot-lib/ui_serial_device.h"

#include <QMetaEnum>

using namespace ::dplot::test;
using namespace ::dplot;
using ::testing::Return;


TEST_F(WindowlessWidgetTest, device_creation_will_enumerate_ports)
{
    SerialPortFactory_Mock factoryMock;

    QStringList fakePorts;
    fakePorts << "COM1" << "COM66";

    EXPECT_CALL(factoryMock, EnumeratePorts()).WillOnce(Return(fakePorts));

    SerialDeviceWidget device(&factoryMock, nullptr);

    EXPECT_STREQ("Disconnect", device.Test_GetUi()->portComboBox->itemText(0).toLatin1());
    EXPECT_STREQ("COM1", device.Test_GetUi()->portComboBox->itemText(1).toLatin1());
    EXPECT_STREQ("COM66", device.Test_GetUi()->portComboBox->itemText(2).toLatin1());
}

///@todo why it does not print values good?
void CompareComboBoxLabels(
        QStringList listExpected, const QString expectedSelected,
        const QComboBox* comboBox, std::string where)
{
    for(int i = 0; i < listExpected.length(); ++i)
    {
        const QString expected = listExpected[i];
        const QString actual = comboBox->itemText(i);
        EXPECT_EQ(expected, actual) << " called at: " << where;
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

    SerialDeviceWidget device(&factoryMock, nullptr);

    auto gui = device.Test_GetUi();


    EXPECT_EQ(115200, gui->baudRateSpinBox->value());

    EXPECT_STREQ("Disconnect", gui->portComboBox->currentText().toLatin1());

    CompareComboBoxLabels({"Data5", "Data6", "Data7", "Data8"},
                          "Data8",
                gui->dataBitsComboBox, AT);

    CompareComboBoxLabels({"NoParity", "EvenParity", "OddParity", "SpaceParity", "MarkParity", "UnknownParity"},
                          "NoParity",
                gui->parityComboBox, AT);

    CompareComboBoxLabels({"OneStop", "OneAndHalfStop", "TwoStop", "UnknownStopBits"},
                          "OneStop",
                gui->stopBitsComboBox, AT);

    CompareComboBoxLabels({"NoFlowControl", "HardwareControl", "SoftwareControl", "UnknownFlowControl"},
                          "NoFlowControl",
                gui->flowControlComboBox, AT);

    EXPECT_STREQ("Disconnected", gui->statusDisplayLabel->text().toLatin1());
}

namespace dplot
{
    ///! Its namespace must match SerialPortConnectionParams to let gtest print it.
    ::std::ostream& operator<<(::std::ostream& os, const SerialPortConnectionParams& params) {
        return os << "SerialPortConnectionParams(" <<
               params.baudRate << "," <<
               (int)params.dataBits << "," <<
               (int)params.flowControl << "," <<
               (int)params.parity << "," <<
               params.port.toStdString() << "," <<
               (int)params.stopBits <<
               ")";
    }
}

TEST_F(WindowlessWidgetTest, connect_button_will_try_to_connect_with_proper_params)
{
    SerialPortFactory_Mock factoryMock;
    QStringList fakePorts{"COM1","COM222", "COM666"};
    EXPECT_CALL(factoryMock, EnumeratePorts()).WillOnce(Return(fakePorts));

    SerialDeviceWidget device(&factoryMock, nullptr);

    Ui::SerialDevice* gui = device.Test_GetUi();
    gui->portComboBox->setCurrentIndex(2); //COM222, disconnect at 0
    gui->baudRateSpinBox->setValue(666);
    gui->dataBitsComboBox->setCurrentIndex(2); //7 data bits
    gui->stopBitsComboBox->setCurrentIndex(2); // 2
    gui->flowControlComboBox->setCurrentIndex(1); //Hardware
    gui->parityComboBox->setCurrentIndex(2); //Odd

    SerialPortConnectionParams expectedParams;
    expectedParams.port = "COM222";
    expectedParams.baudRate = 666;
    expectedParams.dataBits = QSerialPort::Data7;
    expectedParams.stopBits = QSerialPort::TwoStop;
    expectedParams.flowControl = QSerialPort::HardwareControl;
    expectedParams.parity = QSerialPort::OddParity;

    SerialPort_Mock portMock;

    EXPECT_CALL(factoryMock, CreatePort()).
            WillOnce(Return(&portMock));

    EXPECT_CALL(portMock, Reconnect(expectedParams));

    gui->reconnectButton->clicked();
}

///@todo now write some tests for data receiving
