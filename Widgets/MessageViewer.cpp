#include "MessageViewer.h"
#include "misc/Logger.h"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

MessageViewer::MessageViewer(QWidget *parent) :
    QDialog(parent),
    m_pMessageDisplay(NULL)
{
    createActions();
    populateDialog();
    this->setModal(false);
}

MessageViewer::~MessageViewer()
{
    Logger::getInstance()->setDataDisplay(NULL);
}

void MessageViewer::createActions()
{
    QLabel *pDescriptionLabel = new QLabel("Messages input from caster are displayed below:  ");

    m_pMessageDisplay = new QTextEdit();
    m_pMessageDisplay->setReadOnly(true);

    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(pDescriptionLabel);
    pMainLayout->addWidget(m_pMessageDisplay);

    this->setLayout(pMainLayout);
}

void MessageViewer::populateDialog()
{

}
