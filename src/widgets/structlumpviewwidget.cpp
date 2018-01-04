#include "structlumpviewwidget.h"
#include "ui_structlumpviewwidget.h"

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
    ui(new Ui::StructLumpViewWidget)
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
    // TODO: Improve. This is only really a placeholder.
    Q_UNUSED(fragment);

    Q_ASSERT(lumpDef->type() == BSPLumpDef::LumpType::Struct);
    m_pStructLumpDef = lumpDef.staticCast<StructLumpDef>();

    ui->memberTable->setRowCount(m_pStructLumpDef->bspStruct().memberCount());

    for ( int memberIndex = 0; memberIndex < m_pStructLumpDef->bspStruct().memberCount(); ++memberIndex )
    {
        BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().member(memberIndex);
        QString memberName = member->name();

        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, memberName);
        ui->memberTable->setItem(memberIndex, NameColumn, item);
    }
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
