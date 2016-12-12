#ifndef NTRIPSTATUSBAR_H
#define NTRIPSTATUSBAR_H

#include <QStatusBar>
#include <Qlabel>
#include <QDateTime>

class Client;

class NtripStatusbar : public QStatusBar
{
    Q_OBJECT

public:
    explicit NtripStatusbar(QWidget *parent = 0);
    ~NtripStatusbar();

private:
    void createLayout();
    void updateLabels(Client *pClient);
    void timerEvent(QTimerEvent *event);

    QLabel *m_pClientStatusLabel;
    QLabel *m_pClientBytesOutLabel;
    QLabel *m_pTimeLabel;
};

#endif // NTRIPSTATUSBAR_H
