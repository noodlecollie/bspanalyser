#include "valuesearchwidget.h"
#include "ui_valuesearchwidget.h"
#include "model/applicationmodel.h"
#include "bsp/bspfilestructure.h"

ValueSearchWidget::ValueSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueSearchWidget)
{
    ui->setupUi(this);

    connect(ui->lumpSelectWidget, &QListWidget::itemSelectionChanged, this, &ValueSearchWidget::updateSelectAllButtonState);
    connect(ui->selectAllButton, &QPushButton::clicked, this, &ValueSearchWidget::selectAllButtonPressed);
    updateSelectAllButtonState();

    // Populate at the beginning to disable everything that needs it.
    populate();
}

ValueSearchWidget::~ValueSearchWidget()
{
    delete ui;
}

QString ValueSearchWidget::searchProperty() const
{
    return ui->propertySearch->text();
}

QString ValueSearchWidget::searchValue() const
{
    return ui->valueSearch->text();
}

QVector<QString> ValueSearchWidget::searchLumps() const
{
    // TODO
    return QVector<QString>();
}

void ValueSearchWidget::clear()
{
    ui->propertySearch->clear();
    ui->valueSearch->clear();
    ui->lumpSelectWidget->clear();
    clearResultsTable();
}

void ValueSearchWidget::populate()
{
    clear();
    populateLumpSelector();
    refreshGeneralControls();
}

void ValueSearchWidget::populateLumpSelector()
{
    ui->lumpSelectWidget->clear();

    if ( !bspFileIsValid() )
    {
        ui->lumpSelectWidget->setEnabled(false);
        return;
    }

    BSPFileStructure* bspFileStructure = ApplicationModel::globalPointer()->bspFileStructure();
    ui->lumpSelectWidget->setEnabled(true);

    for ( int index = 0; index < bspFileStructure->lumpDefCount(); ++index )
    {
        QSharedPointer<BSPLumpDef> lumpDef = bspFileStructure->lumpDef(index);

        if ( lumpDef->type() == BSPLumpDef::LumpType::Struct )
        {
            ui->lumpSelectWidget->addItem(lumpDef->name());
        }
    }
}

void ValueSearchWidget::clearResultsTable()
{
    ui->resultsView->clear();

    ui->resultsView->setColumnCount(2);
    ui->resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->resultsView->setHorizontalHeaderLabels(QStringList() << tr("Lump") << tr("Item"));
    ui->resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->resultsView->verticalHeader()->setHidden(true);
    ui->resultsView->verticalHeader()->setDefaultSectionSize(20);

    QHeaderView* horizontalHeader = ui->resultsView->horizontalHeader();
    for ( int section = 0; section < ui->resultsView->columnCount(); ++section )
    {
        horizontalHeader->setSectionResizeMode(section, QHeaderView::Stretch);
    }
}

void ValueSearchWidget::refreshGeneralControls()
{
    const bool valid = bspFileIsValid();

    ui->searchButton->setEnabled(valid);
    ui->propertySearch->setEnabled(valid);
    ui->valueSearch->setEnabled(valid);
    ui->resultsView->setEnabled(valid);
    ui->selectAllButton->setEnabled(valid);
}

void ValueSearchWidget::updateSelectAllButtonState()
{
    const int selectedCount = ui->lumpSelectWidget->selectedItems().count();

    if ( selectedCount > 0 )
    {
        ui->selectAllButton->setText(tr("Select None"));
    }
    else
    {
        ui->selectAllButton->setText(tr("Select All"));
    }
}

void ValueSearchWidget::selectAllButtonPressed()
{
    const int selectedCount = ui->lumpSelectWidget->selectedItems().count();

    if ( selectedCount > 0 )
    {
        ui->lumpSelectWidget->clearSelection();
    }
    else
    {
        ui->lumpSelectWidget->selectAll();
    }
}

bool ValueSearchWidget::bspFileIsValid() const
{
    BSPFileStructure* bspFileStructure = ApplicationModel::globalPointer()->bspFileStructure();
    return bspFileStructure && bspFileStructure->lumpDefCount() > 0;
}
