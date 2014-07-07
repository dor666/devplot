#pragma once

#include <QMainWindow>
#include "classes.h"

namespace Ui {
class MainWindow;
}

namespace dplot
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SerialPortFactoryInterface* _serialPortFactory,
                        QWidget *parent = 0);
    ~MainWindow();

public slots:

    void AddDevice();

    void displayError(QString what);

private:
    Ui::MainWindow *ui;

    SerialPortFactoryInterface* serialPortFactory;
};

} // namespace dplot
