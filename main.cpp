#include "mainwindow.h"
#include "styles/FusionStyle.h"
#include "NtripClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new FusionStyle);
    MainWindow w;
    w.show();

    return a.exec();
}
