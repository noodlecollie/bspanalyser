#include "visibilitylumpviewwidget.h"
#include "ui_visibilitylumpviewwidget.h"

#include "model/applicationmodel.h"

VisibilityLumpViewWidget::VisibilityLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisibilityLumpViewWidget),
    m_pLumpDef()
{
    ui->setupUi(this);
}

VisibilityLumpViewWidget::~VisibilityLumpViewWidget()
{
    delete ui;
}

QWidget* VisibilityLumpViewWidget::asWidget()
{
    return this;
}

void VisibilityLumpViewWidget::loadLumpData(const QSharedPointer<BSPLumpDef>& lumpDef, const BSPDataFragment &fragment)
{
    setLumpDef(lumpDef);
    updateLabels();
}

void VisibilityLumpViewWidget::setLumpDef(const QSharedPointer<BSPLumpDef> &lumpDef)
{
    if ( !lumpDef || lumpDef->type() != BSPLumpDef::LumpType::VisData )
    {
        m_pLumpDef = QSharedPointer<VisibilityLumpDef>();
        return;
    }

    m_pLumpDef = lumpDef.staticCast<VisibilityLumpDef>();
}

void VisibilityLumpViewWidget::updateLabels()
{
    ui->lblBytesPerLine->setText(QString::number(calculateNumberOfLeaves()));
    ui->lblTotalLeaves->setText("0");
}

quint32 VisibilityLumpViewWidget::calculateNumberOfLeaves()
{
    if ( !m_pLumpDef )
    {
        return 0;
    }

    QSharedPointer<StructLumpDef> leavesLump = m_pLumpDef->leavesLump();
    BSPDataFragment leavesFragment = leavesLump->getDataFragment(ApplicationModel::globalPointer()->bspFileModel()->contents());

    // TODO: Need length of leaves struct item to go any further.
    return 0;
}
