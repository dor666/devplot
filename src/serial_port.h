#pragma once

#include <QObject>
#include <QSerialPort>

namespace dplot
{

struct SerialPortConnectionParams
{
    QString port;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QSerialPort::Parity parity;

    bool operator==(const SerialPortConnectionParams& other) const
    {
        return
                port == other.port &&
                baudRate == other.baudRate &&
                dataBits == other.dataBits &&
                flowControl == other.flowControl &&
                parity == other.parity;
    }
};

class SerialPortInterface : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortInterface(QObject *parent):
        QObject(parent)
    {
    }

    virtual void Reconnect(const SerialPortConnectionParams& params) = 0;

signals:

    void readyRead();

public slots:
};

class SerialPort : public SerialPortInterface
{

    QSerialPort port;

public:
    explicit SerialPort(QObject *parent = 0) :
        SerialPortInterface(parent)
    {

    }

    void Reconnect(const SerialPortConnectionParams& params) override
    {
        port.setPortName(params.port);
        port.setBaudRate(params.baudRate);
        port.setDataBits(params.dataBits);
        port.setStopBits(params.stopBits);
        port.setFlowControl(params.flowControl);
        port.setParity(params.parity);

        if(port.open(QIODevice::ReadWrite))
        {
            bool success = connect(&port, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
            Q_ASSERT(success);
        }
        else
        {
            ///@todo implement
        }
    }

    ~SerialPort()
    {
        port.close();
    }

    //add reconnect/stop signals and emit data received
};

class SerialPortFactoryInterface : public QObject
{
    Q_OBJECT
public:

    SerialPortFactoryInterface(QObject* parent) :
        QObject(parent)
    {
    }

    virtual QStringList EnumeratePorts() = 0;

    virtual SerialPortInterface* CreatePort() = 0;
};

class SerialPortFactory : public SerialPortFactoryInterface
{
public:

    SerialPortFactory(QObject* parent = nullptr) :
        SerialPortFactoryInterface(parent)
    {
    }

    QStringList EnumeratePorts() override;

    SerialPortInterface* CreatePort() override
    {
        return new SerialPort(this); //this constructor should be private, and friend class added
    }
};

} //namespace dplot
