#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>

class SerialSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

    explicit SerialSettingsDialog(QSerialPort *pPort, QWidget *parent = 0);
    ~SerialSettingsDialog();


private:
    void createActions();
    void populateDialog();

    QComboBox *m_pPortCombo;
    QLabel *m_pPortDescriptionLabel;
    QLabel *m_pPortManufacturerLabel;
    QComboBox *m_pBaudRateCombo;
    QComboBox *m_pDataBitsCombo;
    QComboBox *m_pParityCombo;
    QComboBox *m_pStopBitsCombo;
    QComboBox *m_pFlowControlCombo;

    QSerialPort *m_pSerialPort;
    QDialogButtonBox *pButtonBox;

private slots:
    void apply();
    void onPortComboBoxIndexChanged(int index);
};

#endif // SETTINGSDIALOG_H
