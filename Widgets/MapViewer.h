#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QDialog>

class MapViewer : public QDialog
{
    Q_OBJECT

public:
    explicit MapViewer(QWidget *parent = 0);
    ~MapViewer();

private:
    void createActions();
    void populateDialog();

private slots:

};

#endif // MAPVIEWER_H
