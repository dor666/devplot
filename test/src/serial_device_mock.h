#include "serial_device.h"
#include "gmock/gmock.h"

namespace dplot
{
namespace test
{

class SerialPortFactory_Mock : public SerialPortFactoryInterface
{
public:
    MOCK_METHOD0(EnumeratePorts, QStringList());
};

/*
class SerialDevice_Mock : public SerialDeviceInterface
{

};
*/

} //namespace test
} //namespace dplot
