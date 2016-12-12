#include "SourceTableManager.h"

#include <QDebug>

SourceTableManager::SourceTableManager(QObject *parent)
    : QObject(parent),
      m_pSocket(new QTcpSocket(this))
{
    socketData.clear();
    connect(m_pSocket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onSocketReplied()));
}

SourceTableManager::~SourceTableManager()
{
    while(!m_SourceList.isEmpty()) {
        delete m_SourceList.last();
        m_SourceList.removeLast();
    }

    delete m_pSocket;
}

void SourceTableManager::requestSourceTable(const QString &host, const int port)
{
    m_pSocket->connectToHost(host, port);
}

void SourceTableManager::onSocketConnected()
{
    QString request = "";

    request = "GET / HTTP/1.1\r\n"
              "User-Agent: NTRIP Client/1.0\r\n"
              "Connection: close\r\n"
              "\r\n";

    m_pSocket->write(request.toUtf8());
}

void SourceTableManager::onSocketReplied()
{
    socketData.append(m_pSocket->readAll());

    if(socketData.contains(QString("ENDSOURCETABLE").toLocal8Bit()))
        if (generateSourceList(socketData)) {
            emit sourceManagerTableReceived();

        socketData.clear();
        m_pSocket->abort(); //need to add abort timer
    }
}

bool SourceTableManager::generateSourceList(const QByteArray &data)
{
    bool valid = false;

    QString dataStr;
    dataStr.append(data);

    QStringList list = dataStr.split(QString("\r\n"));

    QString ok = list.first();
    if(ok.contains("200 OK")) {

    #ifdef QT_DEBUG
        foreach(QString item, list) {
            qDebug() << item;
        }
    #endif

    //headers
    for(int i=0; i<6; i++)
        list.removeFirst();

    //delete the old entries
    m_SourceList.empty();

    //start parsing entries
    for(int i=0; i<list.size(); i++) {
        SourceEntry *pNewEntry = createSourceEntry(list.at(i));

        if(pNewEntry != NULL)
            m_SourceList.append(pNewEntry);
    }

        valid = true;
    }

    return valid;
}

SourceEntry* SourceTableManager::createSourceEntry(const QString &line)
{
    SourceEntry* pEntry = new SourceEntry;

    QStringList parameters = line.split(";");

    if(parameters.size() < 2) return NULL; //bad entry

    if(parameters.at(0) == "STR")
        pEntry->type = SourceEntry::eSTR;
    else if(parameters.at(0) == "CAS")
        pEntry->type = SourceEntry::eCAS;
    else if(parameters.at(0) == "NET")
        pEntry->type = SourceEntry::eNET;
    else
        return NULL; //bad entry

    pEntry->mountPtName = parameters.at(1);

    return pEntry;
}

int SourceTableManager::getTotalSourceEntries() const
{
    return m_SourceList.size();
}

SourceEntry* SourceTableManager::getSourceEntry(const int index) const
{
    return m_SourceList.at(index);
}
