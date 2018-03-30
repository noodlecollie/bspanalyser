#include "visibilitylumpviewwidget.h"
#include "ui_visibilitylumpviewwidget.h"
#include "visibilitychartrenderer.h"

#include "model/applicationmodel.h"
#include "bsp/viscompressor.h"

VisibilityLumpViewWidget::VisibilityLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisibilityLumpViewWidget),
    m_pLumpDef(),
    m_nLeafCount(0)
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
    // TODO
    Q_UNUSED(fragment)

    setLumpDef(lumpDef);
    ui->gbInformation->clearError();

    calculateNumberOfLeaves();
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
    ui->lblBytesPerLine->setText(tr("%0 bytes").arg(VisCompressor::bytesRequiredPerCompressedRow(m_nLeafCount)));
    ui->lblTotalLeaves->setText(tr("%0").arg(m_nLeafCount));
}

void VisibilityLumpViewWidget::calculateNumberOfLeaves()
{
    if ( !m_pLumpDef )
    {
        m_nLeafCount = 0;
        return;
    }

    QSharedPointer<StructLumpDef> leavesLump = m_pLumpDef->leavesLump();
    if ( !leavesLump )
    {
        m_nLeafCount = 0;
        return;
    }

    BSPDataFragment leavesFragment = leavesLump->getDataFragment(ApplicationModel::globalPointer()->bspFileModel()->contents());
    quint32 structSize = leavesLump->bspStruct().size();
    quint32 lumpSize = leavesFragment.length();

    if ( lumpSize % structSize != 0 )
    {
        ui->gbInformation->displayError(tr("Leaves lump size (%0 bytes) was not a multiple of the leaf struct size (%1 bytes).")
                                        .arg(lumpSize)
                                        .arg(structSize));
    }

    m_nLeafCount = lumpSize / structSize;
}
