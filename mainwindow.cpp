#include "mainwindow.h"
#include "Widgets/MainWindowWidget.h"
#include "Widgets/MessageViewer.h"
#include "Widgets/MapViewer.h"
#include "Widgets/NtripStatusbar.h"
#include "Misc/Logger.h"
#include "NtripClient.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlComponent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_pNtripClient(NULL)
{
    m_pNtripClient = new NtripClient(this);
    setupGui();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupGui()
{
    m_pMainWidget = new MainWindowWidget(m_pNtripClient, this);
    setCentralWidget(m_pMainWidget);

    QMenuBar *pMenuBar = new QMenuBar(this);
    this->setMenuBar(pMenuBar);
    this->menuBar()->show();
    populateMenuBar(pMenuBar);

    NtripStatusbar *pStatusBar = new NtripStatusbar(this);
    this->setStatusBar(pStatusBar);
}

void MainWindow::populateMenuBar(QMenuBar *pMenuBar)
{
    QMenu *pViewMenu = pMenuBar->addMenu("View");

    QAction* pMessageViewerAct = new QAction(QString("Message Viewer"), this);
    connect(pMessageViewerAct, SIGNAL(triggered()),this,SLOT(openMessageViewer()));
    pViewMenu->addAction(pMessageViewerAct);

    QAction* pMapViewerAct = new QAction(QString("Map Viewer"), this);
    connect(pMapViewerAct, SIGNAL(triggered()),this,SLOT(openMapViewer()));
    pViewMenu->addAction(pMapViewerAct);
}

void MainWindow::openMessageViewer()
{
    MessageViewer dialog(this);
    Logger::getInstance()->setDataDisplay(dialog.getMessageDisplay());
    dialog.exec();
}

void MainWindow::openMapViewer()
{
//    // Using QQmlApplicationEngine
//    QVariantMap parameters;
//    QQmlApplicationEngine engine;
//    engine.load(QUrl::fromLocalFile("QtMapViewer/mapviewer.qml"));
//    //QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));

//    QObject *item = engine.rootObjects().first();
//    Q_ASSERT(item);

//    QMetaObject::invokeMethod(item, "initializeProviders",
//                              Q_ARG(QVariant, QVariant::fromValue(parameters)));

//    // Using QQmlComponent
//    QVariantMap parameters;
//    QQmlEngine engine;
//    QQmlComponent component(&engine,
//            QUrl::fromLocalFile("QtMapViewer/mapviewer.qml"));
//    QObject *object = component.create();
//    QMetaObject::invokeMethod(object, "initializeProviders",
//                              Q_ARG(QVariant, QVariant::fromValue(parameters)));
//    //delete object;


    // Using QQuickView
    QQuickView *pView = new QQuickView;
    pView->setSource(QUrl::fromLocalFile("Qml/mapviewer.qml"));
    pView->setProperty("ResizeMode", QQuickView::SizeRootObjectToView);
    pView->setTitle("Map Viewer");

    QQuickItem * pMapView = pView->rootObject();
    //QQuickItem * pMap = pMapView->findChild<QQuickItem*>("map");
    //Q_ASSERT(pMap);
    //QMultiMap<QString, double> stations;
    QMap<QString, QString> stations;
    stations.insert("Test1","31.00%-115.0");
    stations.insert("Test2","32.00%-116.0");
    stations.insert("Test3","33.00%-117.0");
    stations.insert("Test4","34.00%-118.0");
    stations.insert("Test5","35.00%-119.0");

    QMetaObject::invokeMethod(pMapView, "initializeMap",
                              Q_ARG(QVariant, QVariant::fromValue(stations)));
    pView->show();
}

void MainWindow::onUpdateStatus()
{

}
