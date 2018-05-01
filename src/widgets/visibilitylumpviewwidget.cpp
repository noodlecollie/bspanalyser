#include "visibilitylumpviewwidget.h"
#include "ui_visibilitylumpviewwidget.h"

#include "model/applicationmodel.h"
#include "bsp/viscompressor.h"

#include "util/textutil.h"

namespace
{
    enum TableColumn
    {
        ColLeafPVS = 0,
        ColHex
    };
}

VisibilityLumpViewWidget::VisibilityLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisibilityLumpViewWidget),
    m_pLumpDef(),
    m_nLeafCount(0)
{
    ui->setupUi(this);
    setUpHexDisplay();
    updateAllUi();
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
    setVisData(fragment);

    updateAllUi();
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

void VisibilityLumpViewWidget::updateAllUi()
{
    ui->gbInformation->clearError();

    calculateNumberOfLeaves();
    updateLabels();
    updateTable();
    updateHexDisplay();
}

void VisibilityLumpViewWidget::updateLabels()
{
    ui->lblBytesPerLine->setText(tr("%0 bytes").arg(VisCompressor::bytesRequiredPerUncompressedRow(m_nLeafCount)));
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

void VisibilityLumpViewWidget::updateTable()
{
    ui->leafTable->clear();
    ui->leafTable->setRowCount(m_nLeafCount);
    ui->leafTable->setColumnCount(2);

    ui->leafTable->setHorizontalHeaderLabels(QStringList() << tr("Leaf PVS") << tr("Hex"));

    QStringList verticalHeaderNames;
    for ( quint32 leaf = 0; leaf < m_nLeafCount; ++leaf )
    {
        updateTableRow(leaf, verticalHeaderNames);
    }

    ui->leafTable->setVerticalHeaderLabels(verticalHeaderNames);
}

void VisibilityLumpViewWidget::updateTableRow(quint32 row, QStringList& headers)
{
    headers.append(QString("%0").arg(row));

    QByteArray rowData = VisCompressor().uncompressedRow(m_VisData, m_nLeafCount, row);
    QStringList visibleLeaves;

    for ( quint32 leafIndex = 0; leafIndex < m_nLeafCount; ++leafIndex )
    {
        quint32 byteIndex = leafIndex / 8;

        // TODO: This shouldn't happen, but we're still in the process of
        // sorting out how vis rows should be handled. Don't crash if the
        // index is out of range.
        if ( byteIndex >= rowData.size() )
        {
            break;
        }

        quint32 bitIndex = leafIndex % 8;
        quint8 mask = (1 << bitIndex);

        if ( rowData.at(byteIndex) & mask )
        {
            visibleLeaves.append(QString("%0").arg(leafIndex));
        }
    }

    QTableWidgetItem* leavesItem = new QTableWidgetItem((!visibleLeaves.isEmpty()) ? visibleLeaves.join(", ") : tr("None"));
    ui->leafTable->setItem(row, ColLeafPVS, leavesItem);

    QTableWidgetItem* hexItem = new QTableWidgetItem(TextUtil::hexString(rowData, 4));
    ui->leafTable->setItem(row, ColHex, hexItem);
}

void VisibilityLumpViewWidget::setVisData(const BSPDataFragment &fragment)
{
    m_VisData.clear();

    if ( !m_pLumpDef || !m_pLumpDef->isValid() )
    {
        return;
    }

    if ( !m_pLumpDef->isCompressed() )
    {
        m_VisData = fragment.data();
    }
    else
    {
        VisCompressor().decompress(fragment.data(), m_VisData);
    }

    if ( m_VisData.length() < 1 )
    {
        return;
    }

    quint32 rowSize = VisCompressor::bytesRequiredPerUncompressedRow(m_nLeafCount);

    if ( rowSize > 0 && m_VisData.length() % rowSize != 0 )
    {
        ui->gbInformation->displayError(tr("Visibility lump size (%0 bytes) was not a multiple of the leaf vis row size (%1 bytes).")
                                        .arg(m_VisData.length())
                                        .arg(rowSize));
    }
}

void VisibilityLumpViewWidget::updateHexDisplay()
{
    ui->hexDisplay->setPlainText(TextUtil::hexString(m_VisData, ui->sbVisByteGroupSize->value()));
}

void VisibilityLumpViewWidget::setUpHexDisplay()
{
    ui->hexDisplay->setFont(TextUtil::monospacedFont(ui->hexDisplay->font().pointSize()));
}
