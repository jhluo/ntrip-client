#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    enum eClientState {
        eIdle,
        eConnecting,
        eConnected,
        eDataFlowing,
        eDisconnecting,
        eRetry
    };

    Client(const QString &host, const int port, const QString &mountPt, QObject *parent = 0);
    ~Client();

    void connectClient();
    void disconnectClient();
    eClientState getClientState() {return m_clientState;}

private:
    QTcpSocket *m_pSocket;

    QString m_host;
    int m_port;
    QString m_mountPt;
    eClientState m_clientState;

signals:
    void connectionStateChanged(Client::eClientState state);
    void receievedData(QByteArray &data);

private slots:
    void onSocketConnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketDisconnected();
    void onSocketReplied();
};

#endif // MAINWINDOW_H
