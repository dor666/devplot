#pragma once

#include "serial_device.h"
#include "serial_port.h"
#include "gmock/gmock.h"

namespace dplot
{
namespace test
{

class SerialPortFactory_Mock : public SerialPortFactoryInterface
{
public:
    SerialPortFactory_Mock(QObject* parent = nullptr) : SerialPortFactoryInterface(parent){}

    MOCK_METHOD0(EnumeratePorts, QStringList());
    MOCK_METHOD0(CreatePort, SerialPortInterface*());
};

class SerialPort_Mock : public SerialPortInterface
{
public:

    SerialPort_Mock(QObject* _parent = nullptr) :
        SerialPortInterface(_parent)
    {
    }

    MOCK_METHOD1(Reconnect, void(const SerialPortConnectionParams&));
};

} //namespace test
} //namespace dplot
