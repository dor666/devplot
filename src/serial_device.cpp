#include "serial_device.h"
#include "serial_port.h"
#include "ui_serial_device.h"

#include <QSerialPort>
#include <QMetaEnum>

namespace dplot
{

/// Could be moved to some more general place
template<class T>
void PopulateComboBox(QComboBox* comboBox, const char* enumName, int defaultIndex)
{
    const QMetaObject meta = T::staticMetaObject;

    QMetaEnum metaEnum = meta.enumerator(meta.indexOfEnumerator(enumName));

    for(int i = 0; i < metaEnum.keyCount(); ++i)
    {
        comboBox->addItem(metaEnum.key(i),
                          metaEnum.value(i));
    }

    comboBox->setCurrentIndex(defaultIndex);
}

SerialDeviceWidget::SerialDeviceWidget(SerialPortFactoryInterface* _portFactory, QWidget *parent)
    : QDockWidget(parent)
    ,ui(new Ui::SerialDevice)
    ,portFactory(_portFactory)
{
    ui->setupUi(this);

    RefreshPortList();

    PopulateComboBox<QSerialPort>(ui->dataBitsComboBox, "DataBits", 3);
    PopulateComboBox<QSerialPort>(ui->parityComboBox, "Parity", 0);
    PopulateComboBox<QSerialPort>(ui->stopBitsComboBox, "StopBits", 0);
    PopulateComboBox<QSerialPort>(ui->flowControlComboBox, "FlowControl", 0);

    bool success = connect(ui->reconnectButton, SIGNAL(clicked()),
                           this, SLOT(Reconnect()));
    Q_ASSERT(success);
}

void SerialDeviceWidget::RefreshPortList()
{
    ui->portComboBox->clear();
    ui->portComboBox->addItem(tr("Disconnect"));
    QStringList ports = portFactory->EnumeratePorts();
    foreach(const QString& port, ports)
    {
        ui->portComboBox->addItem(port);
    }
}

SerialPortConnectionParams SerialDeviceWidget::GetParamsFromUi()
{
    SerialPortConnectionParams params;

    params.dataBits = static_cast<QSerialPort::DataBits>(ui->dataBitsComboBox->currentData().toInt());
    params.parity = static_cast<QSerialPort::Parity>(ui->parityComboBox->currentData().toInt());
    params.stopBits = static_cast<QSerialPort::StopBits>(ui->stopBitsComboBox->currentData().toInt());
    params.flowControl = static_cast<QSerialPort::FlowControl>(ui->flowControlComboBox->currentData().toInt());

    params.port = ui->portComboBox->currentText();
    params.baudRate = ui->baudRateSpinBox->value();

    return params;
}

SerialDeviceWidget::~SerialDeviceWidget()
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


