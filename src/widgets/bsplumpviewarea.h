#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>

#include "bsp/bspfilestructure.h"

class ILumpViewWidget;

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

private:
    enum PlaceholderAction
    {
        PlaceholderIgnore,
        PlaceholderCreate,
        PlaceholderRemove
    };

    static QLabel* createPlaceholderTabContents();

    void initDataArea();
    void initLumpTable();
    void clearLumpTable();
    void clearDataArea();
    void updateDataAreaTabs();
    int tabIndexForLump(int lumpIndex) const;
    PlaceholderAction getPlaceholderTabAction() const;
    void loadBSPDataIntoLumpView(const QSharedPointer<BSPLumpDef>& lumpDef, ILumpViewWidget* lumpView);

    QTableWidget* m_pLumpTable;
    QTabWidget* m_pDataArea;
};

#endif // BSPLUMPVIEWAREA_H
