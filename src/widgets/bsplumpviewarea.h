#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>

#include "bsp/bspfilestructure.h"

namespace Ui {
class BSPLumpViewArea;
}

class BSPLumpViewArea : public QWidget
{
    Q_OBJECT

public:
    explicit BSPLumpViewArea(QWidget *parent = 0);
    ~BSPLumpViewArea();

    void updateLumps(const BSPFileStructure& bspFileStructure);

private:
    Ui::BSPLumpViewArea *ui;
};

#endif // BSPLUMPVIEWAREA_H
