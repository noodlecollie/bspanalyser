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
    ui->lblTotalItems->setText(tr("/ %0").arg(m_nItemCount - 1));
    ui->lblBytesPerItem->setText(tr("%0 bytes").arg(m_pStructLumpDef ? m_pStructLumpDef->bspStruct().size() : 0));
    ui->lblLumpSize->setText(tr("%0 bytes").arg(m_LumpData.count()));

    // Signals blocked because we want to manually enforce that lumpItemChanged()
    // is called, which it may not be if the spinbox is already at value 0 when
    // setValue() is called.
    ui->sbItemIndex->blockSignals(true);

    if ( m_nItemCount > 0 )
    {
        ui->sbItemIndex->setMinimum(0);
        ui->sbItemIndex->setMaximum(m_nItemCount - 1);
        ui->sbItemIndex->setValue(0);
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
        QString typeString = DisplayStringConversion::typeString(*member);

        setItem(memberIndex, NameColumn, memberName);
        setItem(memberIndex, TypeColumn, typeString);
        ui->memberTable->setItem(memberIndex, ValueColumn, new QTableWidgetItem());
    }
}

void StructLumpViewWidget::setItem(int row, int column, const QString &data)
{
    // Here's assuming that Qt deletes the previously owned tabe item when setting a new one.
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, data);
    ui->memberTable->setItem(row, column, item);
}

void StructLumpViewWidget::lumpItemChanged(int item)
{
    QByteArray structData = item >= 0 ? getStructData(item) : QByteArray();

    for ( int row = 0; row < ui->memberTable->rowCount(); ++row )
    {
        QTableWidgetItem* tableItem = ui->memberTable->item(row, ValueColumn);
        if ( !tableItem )
        {
            continue;
        }

        // This will be empty if the lump def doesn't exist.
        if ( !structData.isEmpty() )
        {
            BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().member(row);
            QSharedPointer<BSPStructItemTypeConverter> typeConverter = member->typeConverter();

            if ( typeConverter )
            {
                BSPStructItemTypes::CoreItemType coreType = member->itemType();

                if ( member->itemCount() > 1 && !BSPStructItemTypes::coreTypeHasModifier(coreType, BSPStructItemTypes::Mod_InterpretAsString) )
                {
                    QStringList list;

                    for ( quint32 itemIndex = 0; itemIndex < member->itemCount(); ++itemIndex )
                    {
                        list.append(DisplayStringConversion::toString(typeConverter->value(structData, itemIndex),
                                                                      coreType,
                                                                      memberFormatHint(*member)));
                    }

                    tableItem->setData(Qt::DisplayRole, list.join(", "));
                }
                else
                {
                    tableItem->setData(Qt::DisplayRole,
                                  DisplayStringConversion::toString(typeConverter->value(structData, 0),
                                                                    coreType,
                                                                    memberFormatHint(*member)));
                }

                if ( BSPStructItemTypes::unmodifiedCoreType(coreType) == BSPStructItemTypes::Type_RGB8 && member->itemCount() == 1 )
                {
                    QVariant data = typeConverter->value(structData, 0);
                    QColor col = data.value<QColor>();

                    float avg = (col.redF() + col.greenF() + col.blueF()) / 3.0f;
                    if ( avg < 0.5f )
                    {
                        tableItem->setData(Qt::ForegroundRole, QBrush(Qt::white));
                    }

                    tableItem->setData(Qt::BackgroundColorRole, col);
                }
            }
        }
    }
}

quint32 StructLumpViewWidget::memberFormatHint(const BSPStructGenericBlock &member) const
{
    quint32 formatHint = DisplayStringConversion::NoFormatHint;

    if ( BSPStructItemTypes::coreTypeHasModifier(member.itemType(), BSPStructItemTypes::Mod_IsPrimaryOffset) )
    {
        formatHint |= DisplayStringConversion::IntegerAsHex;
    }
    else
    {
        QVariant hexVariant = member.attributes().attributeValue(BSPStructItemAttributes::Attribute::DisplayHex);
        if ( hexVariant.type() == QVariant::Bool && hexVariant.toBool() )
        {
            formatHint |= DisplayStringConversion::IntegerAsHex;
        }
    }

    return formatHint;
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
