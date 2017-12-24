#include "mainwidget.h"

#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_pSplitter(new QSplitter(this)),
      m_pHexDisplayWidget(new HexDisplayWidget())
{
    QLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    m_pSplitter->setOrientation(Qt::Vertical);

    m_pSplitter->addWidget(m_pHexDisplayWidget);

    layout->addWidget(m_pSplitter);
    setLayout(layout);
}

HexDisplayWidget* MainWidget::hexDisplayWidget()
{
    return m_pHexDisplayWidget;
}
