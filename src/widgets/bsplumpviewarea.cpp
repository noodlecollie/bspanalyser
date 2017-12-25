#include "bsplumpviewarea.h"

#include <QSplitter>
#include <QHBoxLayout>
#include <QHeaderView>

namespace
{
    static constexpr int ROW_HEIGHT = 20;
}

BSPLumpViewArea::BSPLumpViewArea(QWidget *parent)
    : QWidget(parent),
      m_pLumpTable(new QTableWidget()),
      m_pDataArea(new QTabWidget()),
      m_bPlaceholderActive(false)
{
    initDataArea();
    initLumpTable();

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setMargin(0);
    hLayout->setSpacing(0);

    QSplitter* splitter = new QSplitter();
    splitter->addWidget(m_pLumpTable);
    splitter->addWidget(m_pDataArea);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 7);

    hLayout->addWidget(splitter);
    setLayout(hLayout);
}

void BSPLumpViewArea::updateLumps(const BSPFileStructure &bspFileStructure)
{
    clearLumpTable();
    m_pLumpTable->setRowCount(bspFileStructure.lumpDefCount());

    for ( int lumpIndex = 0; lumpIndex < bspFileStructure.lumpDefCount(); ++lumpIndex )
    {
        QSharedPointer<BSPLumpDef> lumpDef = bspFileStructure.lumpDef(lumpIndex);
        m_pLumpTable->setItem(lumpIndex, 0, new QTableWidgetItem(lumpDef->name()));
        m_pLumpTable->setRowHeight(lumpIndex, ROW_HEIGHT);
    }
}

void BSPLumpViewArea::initDataArea()
{
    m_pDataArea->tabBar()->setUsesScrollButtons(true);

    connect(m_pDataArea->tabBar(), &QTabBar::tabCloseRequested, this, &BSPLumpViewArea::handleTabCloseRequest);

    clearDataArea();
}

void BSPLumpViewArea::initLumpTable()
{
    connect(m_pLumpTable, &QTableWidget::cellDoubleClicked, this, &BSPLumpViewArea::handleLumpCellDoubleClicked);

    clearLumpTable();
}

void BSPLumpViewArea::clearDataArea()
{
    while ( m_pDataArea->count() > 1 )
    {
        m_pDataArea->removeTab(0);
    }

    updateDataAreaTabs();
}

void BSPLumpViewArea::clearLumpTable()
{
    m_pLumpTable->clear();
    m_pLumpTable->setColumnCount(1);
    m_pLumpTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pLumpTable->setHorizontalHeaderLabels(QStringList() << tr("Lumps"));
    m_pLumpTable->horizontalHeader()->setStretchLastSection(true);
    m_pLumpTable->verticalHeader()->setHidden(true);
}

void BSPLumpViewArea::handleTabCloseRequest(int index)
{
    if ( index < 0 || index >= m_pDataArea->count() )
    {
        return;
    }

    m_pDataArea->removeTab(index);
    updateDataAreaTabs();
}

void BSPLumpViewArea::handleLumpCellDoubleClicked(int row, int column)
{
    if ( column != 0 || row < 0 || row >= m_pLumpTable->rowCount() )
    {
        return;
    }

    int existingTabIndex = tabIndexForLump(row);
    if ( existingTabIndex >= 0 )
    {
        m_pDataArea->setCurrentIndex(existingTabIndex);
        return;
    }

    QTableWidgetItem* item = m_pLumpTable->item(row, column);
    if ( !item )
    {
        return;
    }

    QString lumpName = item->data(Qt::DisplayRole).toString();

    // TODO: Make useful
    m_pDataArea->addTab(new QLabel(QString("This is the tab widget for lump %0.").arg(lumpName)), lumpName);
    updateDataAreaTabs();

    m_pDataArea->setCurrentIndex(m_pDataArea->count() - 1);
    m_pDataArea->tabBar()->setTabData(m_pDataArea->count() - 1, QVariant(row));
}

void BSPLumpViewArea::updateDataAreaTabs()
{
    bool showPlaceholder = !m_bPlaceholderActive && m_pDataArea->count() < 1;

    m_pDataArea->setTabsClosable(!showPlaceholder);

    if ( showPlaceholder )
    {
        m_pDataArea->addTab(createPlaceholderTabContents(), "...");
        m_pDataArea->setTabEnabled(0, false);
        m_bPlaceholderActive = true;
    }
    else if ( m_bPlaceholderActive )
    {
        m_pDataArea->removeTab(0);
        m_bPlaceholderActive = false;
    }
}

int BSPLumpViewArea::tabIndexForLump(int lumpIndex) const
{
    QTabBar* bar = m_pDataArea->tabBar();

    for ( int tabIndex = 0; tabIndex < bar->count(); ++tabIndex )
    {
        QVariant data = bar->tabData(tabIndex);

        if ( data.type() == QVariant::Int && data.toInt() == lumpIndex )
        {
            return tabIndex;
        }
    }

    return -1;
}

QLabel* BSPLumpViewArea::createPlaceholderTabContents()
{
    QLabel* label = new QLabel(tr("No lump selected."));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}
