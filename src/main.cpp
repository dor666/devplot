#include "mainwindow.h"
#include <QApplication>

#include "serial_device.h"

using namespace dplot;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
