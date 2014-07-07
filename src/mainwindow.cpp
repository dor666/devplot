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
    AddDevice();

    bool success = connect(ui->actionAdd_device, SIGNAL(triggered()), this, SLOT(AddDevice()));
    Q_ASSERT(success);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddDevice()
{
    SerialDeviceWidget* newDevice = new SerialDeviceWidget(serialPortFactory);
    addDockWidget(Qt::LeftDockWidgetArea, newDevice);

    bool success = connect(newDevice, SIGNAL(errorOccurred(QString)), this, SLOT(displayError(QString)));
    Q_ASSERT(success);
}

void MainWindow::displayError(QString what)
{
    statusBar()->showMessage(what);
}

} //namespace dplot
