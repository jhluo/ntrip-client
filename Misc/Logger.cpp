#include "Logger.h"
#include <QDateTime>
#include <QDebug>

Logger* Logger::pInstance = 0;

Logger* Logger::getInstance()
{
    if(pInstance == NULL) {
        pInstance = new Logger();
    }

    return pInstance;
}

Logger::Logger(QObject *parent):
    QObject(parent),
    m_DataLogEnabled(false),
    m_SystemLogEnabled(false),
    m_ShowTime(false),
    m_pLogDisplay(NULL),
    m_pDataDisplay(NULL)
{

}


Logger::~Logger()
{
    delete pInstance;
}

void Logger::addSystemDisplay(QTextEdit *pLogDisplay)
{
    m_pLogDisplay = pLogDisplay;
}

void Logger::setDataDisplay(QTextEdit *pDataDisplay)
{
    m_pDataDisplay = pDataDisplay;
}

void Logger::write(const QString &line, const eLogType type)
{
    QString output(line);

    if (m_ShowTime) {
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:  ");
        output.prepend(time);
    }

    QTextEdit *pDisplay = NULL;
    QString filePath ="";
    bool logEnabled = false;

    if(type == eSystem) {
        pDisplay = m_pLogDisplay;
        filePath = m_LogFilePath;
        logEnabled = m_SystemLogEnabled;
    } else if(type == eData) {
        pDisplay = m_pDataDisplay;
        filePath = m_DataFilePath;
        logEnabled = m_DataLogEnabled;
    } else if(type == eDebug) {
        #ifdef QT_DEBUG
            qDebug() << line;
        #endif
    }

    writeToOutput(output, pDisplay);

    if(logEnabled)
        writeToOutput(output, filePath);
}

void Logger::writeToOutput(const QString &line, QTextEdit *pDisplay)
{
    if(pDisplay != NULL)
        pDisplay->append(line);
}

void Logger::writeToOutput(const QString &line, const QString &filePath)
{

}

void Logger::setSystemLogEnabled(const bool enable)
{
    m_SystemLogEnabled = enable;
}


void Logger::setDataLogEnabled(const bool enable)
{
    m_DataLogEnabled = enable;
}



// End of file Logger.cpp
