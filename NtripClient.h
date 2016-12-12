#pragma once

#include <QApplication>
#include <QTcpSocket>
#include <QtSerialPort/QSerialPort>

#include "Client/ClientManager.h"
#include "Client/SourceTableManager.h"

class NtripClient : public QApplication
{
    Q_OBJECT

public:
    NtripClient( int& argc, char **argv );
    ~NtripClient();
    int Run();

private:
    QMainWindow *m_MainWindow
};
