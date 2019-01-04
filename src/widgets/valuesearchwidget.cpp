#include "valuesearchwidget.h"
#include "ui_valuesearchwidget.h"

#include <QtDebug>

#include "model/applicationmodel.h"
#include "bsp/bspfilestructure.h"

ValueSearchWidget::ValueSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueSearchWidget)
{
    ui->setupUi(this);

    connect(ui->lumpSelectWidget, &QListWidget::itemSelectionChanged, this, &ValueSearchWidget::handleItemSelectionChanged);
    connect(ui->selectAllButton, &QPushButton::clicked, this, &ValueSearchWidget::selectAllButtonPressed);
    updateSelectAllButtonState();

    connect(ui->propertySearch, &QLineEdit::textChanged, this, &ValueSearchWidget::refreshSearchButtonEnabledState);
    connect(ui->valueSearch, &QLineEdit::textChanged, this, &ValueSearchWidget::refreshSearchButtonEnabledState);
    connect(ui->resultsView, &QTableWidget::cellDoubleClicked, this, &ValueSearchWidget::handleResultCellDoubleClicked);

    connect(ui->searchButton, &QPushButton::clicked, this, &ValueSearchWidget::performSearch);
    connect(ui->propertySearch, &QLineEdit::returnPressed, this, &ValueSearchWidget::performSearch);
    connect(ui->valueSearch, &QLineEdit::returnPressed, this, &ValueSearchWidget::performSearch);

    // Populate at the beginning to initialise disabled states.
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
    QVector<QString> lumpNames;
    QList<QListWidgetItem*> selectedItems = ui->lumpSelectWidget->selectedItems();

    for ( QListWidgetItem* item : selectedItems )
    {
        lumpNames.append(item->text());
    }

    return lumpNames;
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

    ui->propertySearch->setEnabled(valid);
    ui->valueSearch->setEnabled(valid);
    ui->resultsView->setEnabled(valid);
    ui->selectAllButton->setEnabled(valid);

    refreshSearchButtonEnabledState();
}

void ValueSearchWidget::refreshSearchButtonEnabledState()
{
    ui->searchButton->setEnabled(bspFileIsValid() && canRunSearch());
}

void ValueSearchWidget::handleItemSelectionChanged()
{
    refreshSearchButtonEnabledState();
    updateSelectAllButtonState();
}

void ValueSearchWidget::updateSelectAllButtonState()
{
    const int selectedCount = selectedLumpCount();

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
    const int selectedCount = selectedLumpCount();

    if ( selectedCount > 0 )
    {
        ui->lumpSelectWidget->clearSelection();
    }
    else
    {
        ui->lumpSelectWidget->selectAll();
    }
}

void ValueSearchWidget::performSearch()
{
    ValueSearchWorker& worker = ApplicationModel::globalPointer()->valueSearchWorker();
    QVector<ValueSearchWorker::SearchResult> results = worker.performSearch(ui->propertySearch->text().trimmed(), ui->valueSearch->text(), searchLumps());

    clearResultsTable();
    ui->resultsView->setRowCount(results.count());

    for ( int resultIndex = 0; resultIndex < results.count(); ++resultIndex )
    {
        ValueSearchWorker::SearchResult result = results.at(resultIndex);
        QTableWidgetItem* lump = new QTableWidgetItem(result.lumpName);
        QTableWidgetItem* itemIndex = new QTableWidgetItem(QString("%0").arg(result.itemIndex));

        lump->setData(Qt::UserRole, QVariant(result.lumpIndex));
        itemIndex->setData(Qt::UserRole, QVariant(result.itemIndex));

        ui->resultsView->setItem(resultIndex, 0, lump);
        ui->resultsView->setItem(resultIndex, 1, itemIndex);
    }
}

void ValueSearchWidget::handleResultCellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);

    QTableWidgetItem* lumpIndexItem = ui->resultsView->item(row, 0);
    QTableWidgetItem* itemIndexItem = ui->resultsView->item(row, 1);

    if ( !lumpIndexItem || !itemIndexItem )
    {
        return;
    }

    emit searchResultChosen(lumpIndexItem->data(Qt::UserRole).value<quint32>(),
                            itemIndexItem->data(Qt::UserRole).value<quint32>());
}

bool ValueSearchWidget::bspFileIsValid() const
{
    BSPFileStructure* bspFileStructure = ApplicationModel::globalPointer()->bspFileStructure();
    return bspFileStructure && bspFileStructure->lumpDefCount() > 0;
}

bool ValueSearchWidget::canRunSearch() const
{
    return !ui->propertySearch->text().trimmed().isEmpty() &&
           selectedLumpCount() > 0;
}

int ValueSearchWidget::selectedLumpCount() const
{
    return ui->lumpSelectWidget->selectedItems().count();
}
