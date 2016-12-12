#ifndef SOURCETABLEMANAGER_H
#define SOURCETABLEMANAGER_H

#include <QObject>
#include <QVector>
#include <QTcpSocket>

typedef struct TableEntry {
    enum eType{
        eSTR,
        eCAS,
        eNET
    };

    eType type;
    QString mountPtName;
    QString sourceId;
    QString format;
    QString formatDetail;
    int carrierInfo;
    QString navSystem;
    QString network;
    QString country;
    double latitude;
    double longitude;
    bool sendNmea;
    bool vrs;
    QString generator;
    QString encryption;
    char authentication;
    bool free;
    int bitRate;

} SourceEntry;

class SourceTableManager : public QObject
{
    Q_OBJECT

public:
    SourceTableManager(QObject *parent = 0);
    ~SourceTableManager();

    void requestSourceTable(const QString &host, const int port);
    bool generateSourceList(const QByteArray &data);

    int getTotalSourceEntries() const;
    SourceEntry* getSourceEntry(const int index) const;

private:
    QTcpSocket *m_pSocket;
    QVector<SourceEntry*> m_SourceList;
    QByteArray socketData;

    SourceEntry* createSourceEntry(const QString &line);

signals:
    void sourceManagerTableReceived();

private slots:
    void onSocketConnected();
    void onSocketReplied();

};

#endif // MAINWINDOW_H
