#include "structlumpviewwidget.h"
#include "ui_structlumpviewwidget.h"

#include "bsp/displaystringconversion.h"
#include "exceptions/genericexception.h"

Q_LOGGING_CATEGORY(lcStructLumpViewWidget, "StructLumpViewWidget")

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
    quint32 lumpDataSize = static_cast<quint32>(m_LumpData.count());

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

    ui->sbItemIndex->setMinimum(0);
    ui->sbItemIndex->setMaximum(m_nItemCount > 0 ? static_cast<int>(m_nItemCount - 1) : 0);
    ui->sbItemIndex->setValue(0);

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
    QByteArray structData = getStructData(item);

    for ( int row = 0; row < ui->memberTable->rowCount(); ++row )
    {
        QTableWidgetItem* tableItem = ui->memberTable->item(row, ValueColumn);
        if ( !tableItem )
        {
            continue;
        }

        BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().member(row);
        Q_ASSERT(member);

        QSharedPointer<BSPStructItemTypeConverter> typeConverter = member->typeConverter();
        if ( !typeConverter )
        {
            continue;
        }

        QString displayString;

        try
        {
            displayString = DisplayStringConversion::displayStringFromMemberData(*m_pStructLumpDef, structData, static_cast<quint32>(row));
        }
        catch (const GenericException& ex)
        {
            qCWarning(lcStructLumpViewWidget) << "Error converting value at row" << row << "to string:" << ex.message();
            displayString = QString();
        }

        if ( displayString.isNull() )
        {
            continue;
        }

        tableItem->setData(Qt::DisplayRole, displayString);

        if ( BSPStructItemTypes::unmodifiedCoreType(member->itemType()) == BSPStructItemTypes::Type_RGB8 && member->itemCount() == 1 )
        {
            QVariant data = typeConverter->value(structData, 0);
            QColor col = data.value<QColor>();

            // Change the colour of the text if it would be difficult to read against the background.
            float avg = static_cast<float>(col.redF() + col.greenF() + col.blueF()) / 3.0f;
            if ( avg < 0.5f )
            {
                tableItem->setData(Qt::ForegroundRole, QBrush(Qt::white));
            }

            tableItem->setData(Qt::BackgroundColorRole, col);
        }
    }
}

QByteArray StructLumpViewWidget::getStructData(int item) const
{
    if ( item < 0 || !m_pStructLumpDef )
    {
        return QByteArray();
    }

    try
    {
        return m_pStructLumpDef->getDataForIndex(m_LumpData, static_cast<quint32>(item));
    }
    catch (const GenericException&)
    {
        return QByteArray();
    }
}
