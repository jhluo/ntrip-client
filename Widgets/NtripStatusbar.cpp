#include "NtripStatusbar.h"
#include "Client/Client.h"

NtripStatusbar::NtripStatusbar(QWidget *parent):
    QStatusBar(parent)
{
    createLayout();
    startTimer(1000);
}

NtripStatusbar::~NtripStatusbar()
{

}

void NtripStatusbar::createLayout()
{
    m_pClientStatusLabel = new QLabel("IDLE", this);
    m_pClientBytesOutLabel = new QLabel(this);
    m_pTimeLabel = new QLabel(this);

    this->addWidget(m_pClientStatusLabel);
    this->addWidget(m_pClientBytesOutLabel);
    this->addWidget(m_pTimeLabel);
}

void NtripStatusbar::timerEvent(QTimerEvent *event)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    m_pTimeLabel->setText(currentTime.toString("yyyy-MM-dd HH:mm:ss"));
}

void NtripStatusbar::updateLabels(Client *pClient)
{

}
