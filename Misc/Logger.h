#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QTextEdit>
#include <QIODevice>

#define LOG_SYS(line)   Logger::getInstance()->write(line, Logger::eSystem)
#define LOG_DATA(line)  Logger::getInstance()->write(line, Logger::eData)
#define LOG_DEBUG(line) Logger::getInstance()->write(line, Logger::eDebug)

class Logger : public QObject
{
        Q_OBJECT

public:

    enum eLogType {
        eSystem,
        eData,
        eDebug,
    };

    static Logger* getInstance();
    ~Logger();

    void addSystemDisplay(QTextEdit *pLogDisplay);
    void setDataDisplay(QTextEdit *pDataDisplay);

    void write(const QString &line, const eLogType type);

    void setDataLogEnabled(const bool enable);
    bool getDataLogEnabled() const {return m_DataLogEnabled;}

    void setSystemLogEnabled(const bool enable);
    bool getSystemLogEnabled() const {return m_SystemLogEnabled;}

    void setShowTime(const bool enable);
    bool getShowTime() const {return m_ShowTime;}

private:
    explicit Logger(QObject *parent = 0);
    static Logger *pInstance;

    void writeToOutput(const QString &line, const QString &filePath);
    void writeToOutput(const QString &line, QTextEdit *pDisplay);

    bool m_DataLogEnabled;
    bool m_SystemLogEnabled;
    bool m_ShowTime;

    QString m_LogFilePath;
    QString m_DataFilePath;

    QTextEdit *m_pLogDisplay;
    QTextEdit *m_pDataDisplay;
};

#endif // LOGGER_H

