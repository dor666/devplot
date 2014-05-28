#pragma once

#include <QDockWidget>
#include <QSerialPortInfo>

namespace Ui {
class SerialDevice;
}

namespace dplot
{

class SerialPortFactoryInterface
{
public:
    virtual QStringList EnumeratePorts() = 0;
};

class SerialPortFactory : public SerialPortFactoryInterface
{
public:
    QStringList EnumeratePorts() override;
};

class SerialDevice : public QDockWidget
{

    Q_OBJECT

public:

    SerialDevice(SerialPortFactoryInterface* _portFactory, QWidget *parent);

    ~SerialDevice();

private:

    Ui::SerialDevice *ui;

    SerialPortFactoryInterface* portFactory = nullptr;

    void RefreshPortList();

public:

    Ui::SerialDevice* Test_GetUi()
    {
        return ui;
    }
};

} //namespace dplot
