#include "serial_device.h"
#include "ui_serial_device.h"
#include <QSerialPort>

namespace dplot
{

SerialDevice::SerialDevice(SerialPortFactoryInterface* _portFactory, QWidget *parent)
    : QDockWidget(parent)
    ,ui(new Ui::SerialDevice)
    ,portFactory(_portFactory)
{
    ui->setupUi(this);

    RefreshPortList();

    ui->dataBitsComboBox->addItem("5", QSerialPort::Data5);
    ui->dataBitsComboBox->addItem("6", QSerialPort::Data6);
    ui->dataBitsComboBox->addItem("7", QSerialPort::Data7);
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);
    ui->dataBitsComboBox->setCurrentIndex(3);

    ui->parityComboBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityComboBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityComboBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityComboBox->addItem(tr("Space"), QSerialPort::SpaceParity);
    ui->parityComboBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityComboBox->setCurrentIndex(0);

    ui->stopBitsComboBox->addItem(tr("1"), QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    ui->stopBitsComboBox->addItem(tr("2"), QSerialPort::TwoStop);
    ui->stopBitsComboBox->setCurrentIndex(0);

    ui->flowControlComboBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlComboBox->addItem(tr("Hardware"), QSerialPort::HardwareControl);
    ui->flowControlComboBox->addItem(tr("Software"), QSerialPort::SoftwareControl);
    ui->flowControlComboBox->setCurrentIndex(0);
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


