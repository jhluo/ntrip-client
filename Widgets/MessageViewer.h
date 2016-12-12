#ifndef MESSAGEVIEWER_H
#define MESSAGEVIEWER_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QTextEdit>
#include <QButtonGroup>

class MessageViewer : public QDialog
{
    Q_OBJECT

public:
    explicit MessageViewer(QWidget *parent = 0);
    ~MessageViewer();

    QTextEdit *getMessageDisplay() {return m_pMessageDisplay;}

private:
    void createActions();
    void populateDialog();

    QTextEdit *m_pMessageDisplay;

private slots:

};

#endif // MESSAGEVIEWER_H
