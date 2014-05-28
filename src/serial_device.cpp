#include "serial_device.h"
#include "ui_serial_device.h"

namespace dplot
{

SerialDevice::SerialDevice(SerialPortFactoryInterface* _portFactory, QWidget *parent)
    : QDockWidget(parent)
    ,ui(new Ui::SerialDevice)
    ,portFactory(_portFactory)
{
    ui->setupUi(this);

    RefreshPortList();
}

void SerialDevice::RefreshPortList()
{
    ui->portComboBox->clear();
    ui->portComboBox->addItem(tr("Disconnect"));
    QStringList ports = portFactory->EnumeratePorts();
    foreach(const QString& port, ports)
    {
        ui->portComboBox->addItem(port);
    }
}

SerialDevice::~SerialDevice()
{
    delete ui;
}

QStringList SerialPortFactory::EnumeratePorts()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList ret;
    ret.reserve(ports.size());

    foreach(const QSerialPortInfo& port, ports)
    {
        ret.push_back(port.portName());
    }

    return ret;
}

} //namespace dplot
