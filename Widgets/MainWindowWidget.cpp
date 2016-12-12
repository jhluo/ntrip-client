#include "MainWindowWidget.h"
#include "SerialSettingsDialog.h"
#include "NtripClient.h"
#include "Misc/Logger.h"


#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#define BUTTON_SIZE 50

MainWindowWidget::MainWindowWidget(NtripClient *pApp, QWidget *parent)
    : QWidget(parent),
      m_pClientApp(pApp)
{
    createLayout();
    populateWidgets();
    connect(m_pClientApp, SIGNAL(sourceTableReceived()), this, SLOT(onSourceTableReceived()));
    connect(m_pClientApp, SIGNAL(clientConnectionChanged(bool)), this, SLOT(onClientConnectionChanged(bool)));
}

MainWindowWidget::~MainWindowWidget()
{

}

void MainWindowWidget::createLayout()
{
    //NTRIP caster settings group
    QGroupBox *pNtripSettingsBox = new QGroupBox("NTRIP Caster Settings");

    m_pHostEdit = new QLineEdit(this);
    m_pPortEdit = new QLineEdit(this);

    m_pMountPtCombo = new QComboBox(this);
    m_pUpdateButton = new QPushButton("Update", this);
    m_pUpdateButton->setFixedWidth(BUTTON_SIZE);
    connect(m_pUpdateButton, SIGNAL(pressed()), this, SLOT(onUpdateButtonPressed()));

    QHBoxLayout *pMountPtLayout = new QHBoxLayout(this);
    pMountPtLayout->addWidget(m_pMountPtCombo);
    pMountPtLayout->addWidget(m_pUpdateButton);
    QWidget *pMountPtWidget = new QWidget(this);
    pMountPtWidget->setLayout(pMountPtLayout);

    QFormLayout *pCasterSettingsLayout = new QFormLayout();
    pCasterSettingsLayout->setLabelAlignment(Qt::AlignVCenter);
    pCasterSettingsLayout->setFormAlignment(Qt::AlignVCenter);
    pCasterSettingsLayout->addRow("Host", m_pHostEdit);
    pCasterSettingsLayout->addRow("Port", m_pPortEdit);
    pCasterSettingsLayout->addRow("Mount Point", pMountPtWidget);

    pNtripSettingsBox->setLayout(pCasterSettingsLayout);


    //Serial Settings group
    QGroupBox *pSerialSettingsBox = new QGroupBox("Serial Output Settings");

    m_pSerialPortCombo = new QComboBox();

    QFormLayout *pPortLayout = new QFormLayout();
    pPortLayout->addRow("Serial Port:", m_pSerialPortCombo);

    m_pSerialEditButton = new QPushButton("Edit", this);
    m_pSerialEditButton->setFixedWidth(50);
    connect(m_pSerialEditButton, SIGNAL(pressed()), this, SLOT(onSerialEditButtonPressed()));

    QHBoxLayout *pSerialHLayout = new QHBoxLayout();
    pSerialHLayout->addLayout(pPortLayout);
    pSerialHLayout->addWidget(m_pSerialEditButton);

    pSerialSettingsBox->setLayout(pSerialHLayout);

    m_pConnectButton = new QPushButton("Connect", this);
    connect(m_pConnectButton, SIGNAL(pressed()), this, SLOT(onConnectButtonPressed()));

    m_pDisplayEdit = new QTextEdit(this);
    m_pDisplayEdit->setReadOnly(true);
    Logger::getInstance()->addSystemDisplay(m_pDisplayEdit);

    QVBoxLayout *pMainLayout = new QVBoxLayout();
    pMainLayout->addWidget(pNtripSettingsBox);
    pMainLayout->addWidget(pSerialSettingsBox);
    pMainLayout->addWidget(m_pConnectButton);
    pMainLayout->addWidget(m_pDisplayEdit);

    setLayout(pMainLayout);
}

void MainWindowWidget::populateWidgets()
{

}

void MainWindowWidget::onUpdateButtonPressed()
{
    m_pClientApp->requestSourceTable(m_pHostEdit->text(), m_pPortEdit->text().toInt());
}

void MainWindowWidget::onSerialEditButtonPressed()
{
    QSerialPort *pPort = m_pClientApp->getOutputSerial();

    SerialSettingsDialog dialog(pPort, this);
    dialog.exec();
}

void MainWindowWidget::onConnectButtonPressed()
{
    if (!m_pClientApp->isClientConnected()) {
        if(!m_pClientApp->hasSourceTable())
            return;

        m_pClientApp->connectClient(m_pHostEdit->text(), m_pPortEdit->text().toInt(), m_pMountPtCombo->currentText());
    } else {
        m_pClientApp->disconnectClient();
    }
}

void MainWindowWidget::onSourceTableReceived()
{
    //clear the old items
    m_pMountPtCombo->clear();
    m_pMountPtCombo->addItems(m_pClientApp->getMountPtList());
}

void MainWindowWidget::onClientConnectionChanged(bool connected)
{
    if(connected) {
        m_pConnectButton->setText("Disconnect");
        m_pSerialEditButton->setEnabled(false);
    } else {
        m_pConnectButton->setText("Connect");
        m_pSerialEditButton->setEnabled(true);
    }
}
