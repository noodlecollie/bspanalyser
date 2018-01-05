#include "infodisplaygroupbox.h"

#include <QLabel>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

InfoDisplayGroupBox::InfoDisplayGroupBox(QWidget *parent)
    : QGroupBox(parent),
      m_pErrorLabel(nullptr)
{

}

void InfoDisplayGroupBox::displayError(const QString &error)
{
    clearError();

    if ( error.isEmpty() )
    {
        return;
    }

    m_pErrorLabel = new QLabel(QString("<span style=\"color:red;\">%0</span>").arg(error));
    QLayout* currentLayout = layout();

    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(currentLayout);
    if ( gridLayout )
    {
        gridLayout->addWidget(m_pErrorLabel, gridLayout->rowCount(), 0, 1, -1);
        return;
    }

    QFormLayout* formLayout = qobject_cast<QFormLayout*>(currentLayout);
    if ( formLayout )
    {
        formLayout->addRow(m_pErrorLabel);
        return;
    }

    QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(currentLayout);
    if ( vLayout )
    {
        vLayout->addWidget(m_pErrorLabel);
        return;
    }

    QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(currentLayout);
    if ( hLayout )
    {
        hLayout->addWidget(m_pErrorLabel);
        return;
    }

    delete m_pErrorLabel;
    m_pErrorLabel = nullptr;
}

void InfoDisplayGroupBox::clearError()
{
    if ( !m_pErrorLabel )
    {
        return;
    }

    layout()->removeWidget(m_pErrorLabel);
    delete m_pErrorLabel;
    m_pErrorLabel = nullptr;
}
