#ifndef MAINWINDOWWIDGET_H
#define MAINWINDOWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>

class NtripClient;

class MainWindowWidget : public QWidget
{
    Q_OBJECT

public:
    MainWindowWidget(NtripClient *pApp, QWidget *parent = 0);
    ~MainWindowWidget();

private:
    void createLayout();
    void populateWidgets();

    //NTRIP Caster settings
    QLineEdit *m_pHostEdit;
    QLineEdit *m_pPortEdit;
    QComboBox *m_pMountPtCombo;
    QPushButton *m_pUpdateButton;

    //Serial Settings
    QComboBox *m_pSerialPortCombo;
    QPushButton *m_pSerialEditButton;

    //Operation
    QPushButton *m_pConnectButton;
    QCheckBox *m_pLogFileCheckBox;
    QTextEdit *m_pDisplayEdit;

    NtripClient *m_pClientApp;

private slots:
    void onUpdateButtonPressed();
    void onSerialEditButtonPressed();
    void onConnectButtonPressed();
    void onSourceTableReceived();
    void onClientConnectionChanged(bool connected);

};

#endif // MAINWINDOWWIDGET_H
