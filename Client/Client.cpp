#include "Client.h"
#include "misc/Logger.h"


Client::Client(const QString &host, const int port, const QString &mountPt, QObject *parent)
    : QObject(parent),
      m_pSocket(new QTcpSocket(this)),
      m_host(host),
      m_port(port),
      m_mountPt(mountPt),
      m_clientState(eIdle)
{
    connect(m_pSocket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onSocketReplied()));
}

Client::~Client()
{
    delete m_pSocket;
}

void Client::connectClient()
{
    m_pSocket->connectToHost(m_host, m_port);
    m_clientState = eConnecting;
}

void Client::disconnectClient()
{
    m_clientState = eDisconnecting;
    m_pSocket->disconnectFromHost();

}

void Client::onSocketConnected()
{
    m_clientState = eConnected;
    emit connectionStateChanged(m_clientState);

    //send GNSS data request
    QString request = "";

    request = QString("GET /%1 HTTP/1.1\r\n"
               "User-Agent: NTRIP Client\r\n"
               "Accept: */*\r\n"
               "Connection: close\r\n"
               "\r\n").arg(m_mountPt);

    m_pSocket->write(request.toUtf8());
}

void Client::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << error;
}

void Client::onSocketDisconnected()
{
    if(m_clientState != eDisconnecting) {   //not intentional disconnecting
        m_clientState = eRetry;
    } else {
        m_clientState = eIdle;
    }

    emit connectionStateChanged(m_clientState);
}

void Client::onSocketReplied()
{
    QByteArray data;
    data = m_pSocket->readAll();
    if (m_clientState != eDataFlowing
        && data.contains("200 OK")) {
        m_clientState = eDataFlowing;
    } else {
        if(m_clientState == eDataFlowing) {
            LOG_DATA(data);
            emit receievedData(data);
        } else {
          ;
        }
    }
}
