#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class MainWindowWidget;
class NtripClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupGui();
    void populateMenuBar(QMenuBar *pMenuBar);

    MainWindowWidget *m_pMainWidget;
    NtripClient *m_pNtripClient;

private slots:
    void openMessageViewer();
    void openMapViewer();
    void onUpdateStatus();
};

#endif // MAINWINDOW_H
