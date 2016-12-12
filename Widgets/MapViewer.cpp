#include "MapViewer.h"
#include "misc/Logger.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QQuickView>

MapViewer::MapViewer(QWidget *parent) :
    QDialog(parent)
{
    createActions();
    populateDialog();
}

MapViewer::~MapViewer()
{

}

void MapViewer::createActions()
{
    QLabel *pDescriptionLabel = new QLabel("Map is displayed below:  ");

    // Using QQuickView
    QQuickView *pView = new QQuickView;
    pView->setSource(QUrl::fromLocalFile("Qml/helloWorld.qml"));
    QWidget *container = QWidget::createWindowContainer(pView, this);
    //container->setMinimumSize(300, 200);
    //container->setMaximumSize(300, 200);

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(pDescriptionLabel);
    pMainLayout->addWidget(container);

    this->setLayout(pMainLayout);
}

void MapViewer::populateDialog()
{

}
