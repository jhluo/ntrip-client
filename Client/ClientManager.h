#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QVector>
#include <QTcpSocket>

#include "SourceTableManager.h"
#include "Client.h"

class ClientManager : public QObject
{
    Q_OBJECT

public:
    ClientManager(QObject *parent = 0);
    ~ClientManager();

    //Source table related
    void requestSourceTable(const QString &host, const int port);
    bool hasSourceTable() const {return receivedSourceTable;}
    QStringList getMountPtList() const;

    //Client related
    bool isClientConnected() const;
    void connectClient(const QString &host, const int port, const QString &mountPt);
    void disconnectClient();


    //Serial output
    QSerialPort* getOutputSerial() {return m_pOutputSerial;}
    void setOutputSerial(QSerialPort *pPort);

private:
    Client* m_pClient;
    SourceTableManager *m_pSourceManager;

    QSerialPort *m_pOutputSerial;

    bool receivedSourceTable;

signals:
    void sourceTableReceived();
    void clientConnectionChanged(bool connected);

private slots:
    void onSourceManagerTableReceived();
    void onClientStateChanged(Client::eClientState state);
    void onClientReceivedData(QByteArray &data);
};

#endif // MAINWINDOW_H
