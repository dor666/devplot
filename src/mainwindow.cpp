#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

#include "serial_device.h"

namespace dplot
{

MainWindow::MainWindow(SerialPortFactoryInterface* _serialPortFactory,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPortFactory(_serialPortFactory)
{
    ui->setupUi(this);
    addDockWidget(Qt::LeftDockWidgetArea, new SerialDevice(serialPortFactory));
}

MainWindow::~MainWindow()
{
    delete ui;
}

} //namespace dplot
