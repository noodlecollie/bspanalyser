#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>

#include "bsp/bspfilestructure.h"

class BSPLumpViewArea : public QWidget
{
    Q_OBJECT
public:
    explicit BSPLumpViewArea(QWidget *parent = nullptr);

    void setBSPFileStructure(const BSPFileStructure* fileStructure);
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

    QTableWidget* m_pLumpTable;
    QTabWidget* m_pDataArea;
    const BSPFileStructure* m_pBSPFileStructure;
};

#endif // BSPLUMPVIEWAREA_H
