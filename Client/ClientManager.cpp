#include "ClientManager.h"
#include "Client.h"



ClientManager::ClientManager(QObject *parent)
    : QObject(parent)
    m_pClient(NULL),
    m_pSourceManager(NULL),
    m_pOutputSerial(NULL)
{
    m_pSourceManager = new SourceTableManager(this);
    connect(m_pSourceManager, SIGNAL(sourceManagerTableReceived()), this, SLOT(onSourceManagerTableReceived()));
}

ClientManager::~ClientManager()
{

}

void NtripClient::requestSourceTable(const QString& host, const int port)
{
    if(host.isEmpty() || port < 1)
        return;

    m_pSourceManager->requestSourceTable(host, port);
}

QStringList NtripClient::getMountPtList() const
{
    QStringList list;

    for(int i=0; i<m_pSourceManager->getTotalSourceEntries(); i++) {
        list.append(m_pSourceManager->getSourceEntry(i)->mountPtName);
    }

    return list;
}

bool NtripClient::isClientConnected() const
{
    bool connected = false;

    if (m_pClient != NULL) {
        Client::eClientState state = m_pClient->getClientState();

        if (state != Client::eIdle) {
            connected = true;
        }
    }

    return connected;
}

void NtripClient::connectClient(const QString &host, const int port, const QString &mountPt)
{
    if(m_pClient != NULL) {
        m_pClient->disconnect();
        delete m_pClient;
    }

    m_pClient = new Client(host, port, mountPt, this);
    connect(m_pClient, SIGNAL(connectionStateChanged(Client::eClientState)), this, SLOT(onClientStateChanged(Client::eClientState)));
    m_pClient->connectClient();
}

void NtripClient::disconnectClient()
{
    m_pClient->disconnectClient();
}

void NtripClient::onSourceManagerTableReceived()
{
    receivedSourceTable = true;
    emit sourceTableReceived();
}

void NtripClient::onClientStateChanged(Client::eClientState state)
{
    if(state == Client::eConnected) {
        emit clientConnectionChanged(true);
    } else if (state == Client::eIdle) {
        emit clientConnectionChanged(false);
    }
}

void NtripClient::onClientReceivedData(QByteArray &data)
{
    if(m_pOutputSerial != NULL)
        m_pOutputSerial->write(data);
}

void NtripClient::setOutputSerial(QSerialPort *pPort)
{
    if(m_pOutputSerial != NULL)
        delete m_pOutputSerial;

    m_pOutputSerial = pPort;
}



