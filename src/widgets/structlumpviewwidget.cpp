#include "structlumpviewwidget.h"
#include "ui_structlumpviewwidget.h"

#include "displaystringconversion.h"

namespace
{
    enum TableColumn
    {
        NameColumn = 0,
        TypeColumn,
        ValueColumn,

        TableColumnCount
    };
}

StructLumpViewWidget::StructLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StructLumpViewWidget),
    m_pStructLumpDef(),
    m_LumpData(),
    m_nItemCount(0)
{
    ui->setupUi(this);

    initTable();
}

StructLumpViewWidget::~StructLumpViewWidget()
{
    delete ui;
}

QWidget* StructLumpViewWidget::asWidget()
{
    return this;
}

void StructLumpViewWidget::loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment)
{
    Q_ASSERT(lumpDef->type() == BSPLumpDef::LumpType::Struct);
    m_pStructLumpDef = lumpDef.staticCast<StructLumpDef>();
    m_LumpData = fragment.data();

    updateLumpItemCount();
    setTableMemberDefinitions();
    updateUI();
}

void StructLumpViewWidget::initTable()
{
    ui->memberTable->setColumnCount(TableColumnCount);
    ui->memberTable->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Type") << tr("Value"));
    ui->memberTable->verticalHeader()->setDefaultSectionSize(20);

    QHeaderView* horizontalHeader = ui->memberTable->horizontalHeader();
    for ( int column = NameColumn; column < TableColumnCount; ++column )
    {
        if ( column == ValueColumn )
        {
            horizontalHeader->setSectionResizeMode(column, QHeaderView::Stretch);
        }
        else
        {
            horizontalHeader->setSectionResizeMode(column, QHeaderView::ResizeToContents);
        }
    }
}

void StructLumpViewWidget::updateLumpItemCount()
{
    if ( !m_pStructLumpDef )
    {
        m_nItemCount = 0;
        return;
    }

    quint32 structSize = m_pStructLumpDef->bspStruct().size();
    quint32 lumpDataSize = m_LumpData.count();

    if ( lumpDataSize % structSize != 0 )
    {
        ui->gbInformation->displayError(tr("Lump size (%0 bytes) was not a multiple of the struct size (%1 bytes).")
                                        .arg(lumpDataSize)
                                        .arg(structSize));
    }

    m_nItemCount = lumpDataSize/structSize;
}

void StructLumpViewWidget::updateUI()
{
    ui->lblTotalItems->setText(tr("/ %0").arg(m_nItemCount));
    ui->lblBytesPerItem->setText(tr("%0 bytes").arg(m_pStructLumpDef ? m_pStructLumpDef->bspStruct().size() : 0));
    ui->lblLumpSize->setText(tr("%0 bytes").arg(m_LumpData.count()));

    // Signals blocked because we want to manually enforce that lumpItemChanged()
    // is called, which it may not be if the spinbox is already at value 0 when
    // setValue() is called.
    ui->sbItemIndex->blockSignals(true);

    if ( m_nItemCount > 0 )
    {
        ui->sbItemIndex->setMinimum(1);
        ui->sbItemIndex->setMaximum(m_nItemCount);
        ui->sbItemIndex->setValue(1);
    }
    else
    {
        ui->sbItemIndex->setMinimum(0);
        ui->sbItemIndex->setMaximum(0);
        ui->sbItemIndex->setValue(0);
    }

    ui->sbItemIndex->blockSignals(false);

    // If the item index isn't valid, the table cells will be emptied.
    lumpItemChanged(ui->sbItemIndex->value());
}

void StructLumpViewWidget::setTableMemberDefinitions()
{
    ui->memberTable->clearContents();

    if ( !m_pStructLumpDef )
    {
        return;
    }

    ui->memberTable->setRowCount(m_pStructLumpDef->bspStruct().memberCount());

    for ( int memberIndex = 0; memberIndex < m_pStructLumpDef->bspStruct().memberCount(); ++memberIndex )
    {
        BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().member(memberIndex);
        QString memberName = member->name();

        setNameItem(memberIndex, memberName);
        // TODO: Types
        ui->memberTable->setItem(memberIndex, ValueColumn, new QTableWidgetItem());
    }
}

void StructLumpViewWidget::setNameItem(int row, const QString &memberName)
{
    // Here's assuming that Qt deletes the previously owned tabe item when setting a new one.
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, memberName);
    ui->memberTable->setItem(row, NameColumn, item);
}

void StructLumpViewWidget::lumpItemChanged(int item)
{
    // Item index from the spinbox is 1-based.
    --item;

    QByteArray structData = item >= 0 ? getStructData(item) : QByteArray();

    for ( int row = 0; row < ui->memberTable->rowCount(); ++row )
    {
        QTableWidgetItem* item = ui->memberTable->item(row, ValueColumn);
        if ( !item )
        {
            continue;
        }

        QVariant dataToSet;

        // This will be empty if the lump def doesn't exist.
        if ( !structData.isEmpty() )
        {
            BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().member(row);
            QSharedPointer<BSPStructItemTypeConverter> typeConverter = member->typeConverter();

            if ( typeConverter )
            {
                // TODO: Handle arrays.
                dataToSet = typeConverter->value(structData, 0);
            }
        }

        item->setData(Qt::DisplayRole, DisplayStringConversion::toString(dataToSet));
    }
}

QByteArray StructLumpViewWidget::getStructData(quint32 item) const
{
    if ( m_LumpData.isEmpty() || !m_pStructLumpDef )
    {
        return QByteArray();
    }

    quint32 structSize = m_pStructLumpDef->bspStruct().size();
    quint32 endOfRequestedItem = (item + 1) * structSize;

    if ( endOfRequestedItem > static_cast<quint32>(m_LumpData.count()) )
    {
        return QByteArray();
    }

    return m_LumpData.mid(item * structSize, structSize);
}
