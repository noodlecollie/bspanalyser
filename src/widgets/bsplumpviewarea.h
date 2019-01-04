#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>

#include "bsp/bspfilestructure.h"

class ILumpViewWidget;
class ValueSearchWidget;

class BSPLumpViewArea : public QWidget
{
    Q_OBJECT
public:
    explicit BSPLumpViewArea(QWidget *parent = nullptr);

    void updateLumps();

signals:

public slots:

private slots:
    void handleTabCloseRequest(int index);
    void handleLumpCellDoubleClicked(int row, int column);
    void handleSearchResultChosen(quint32 lumpIndex, quint32 itemIndex);

private:
    enum PlaceholderAction
    {
        PlaceholderIgnore,
        PlaceholderCreate,
        PlaceholderRemove
    };

    static QLabel* createPlaceholderTabContents();

    void initSideTabWidget();
    void initDataArea();
    void initLumpTable();
    void clearDataArea();
    void updateDataAreaTabs();
    int tabIndexForLump(int lumpIndex) const;
    PlaceholderAction getPlaceholderTabAction() const;
    void loadBSPDataIntoLumpView(const QSharedPointer<BSPLumpDef>& lumpDef, ILumpViewWidget* lumpView);
    void openTabForLump(int lumpIndex);

    QTabWidget* m_pSideTabWidget;
    QTableWidget* m_pLumpTable;
    ValueSearchWidget* m_pValueSearchWidget;
    QTabWidget* m_pDataArea;
};

#endif // BSPLUMPVIEWAREA_H
