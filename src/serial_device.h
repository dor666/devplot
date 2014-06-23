#pragma once

#include <QDockWidget>
#include <QSerialPortInfo>

#include "serial_port.h"
#include "classes.h"

namespace dplot
{

class SerialDeviceWidget : public QDockWidget
{

    Q_OBJECT

public:

    SerialDeviceWidget(SerialPortFactoryInterface* _portFactory, QWidget *parent = 0);

    ~SerialDeviceWidget();

private:

    Ui::SerialDevice *ui;

    SerialPortFactoryInterface* portFactory = nullptr;

    SerialPortInterface* serialPort = nullptr;

    void RefreshPortList();

    SerialPortConnectionParams GetParamsFromUi();

public slots:

    void ReadyReadSlot()
    {
        ///@todo implement
    }

    void Reconnect()
    {
        delete serialPort;
        serialPort = portFactory->CreatePort();
        serialPort->Reconnect(GetParamsFromUi());

        bool success = connect(serialPort, SIGNAL(readyRead()), this, SLOT(ReadyReadSlot()));
        Q_ASSERT(success);
    }

public:

    Ui::SerialDevice* Test_GetUi()
    {
        return ui;
    }
};

} //namespace dplot
