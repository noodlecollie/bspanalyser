#include "bsplumpviewarea.h"
#include "ui_bsplumpviewarea.h"

BSPLumpViewArea::BSPLumpViewArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BSPLumpViewArea)
{
    ui->setupUi(this);
}

BSPLumpViewArea::~BSPLumpViewArea()
{
    delete ui;
}

void BSPLumpViewArea::updateLumps(const BSPFileStructure &bspFileStructure)
{
    for ( int lumpIndex = 0; lumpIndex < bspFileStructure.lumpDefCount(); ++lumpIndex )
    {
        QSharedPointer<BSPLumpDef> lumpDef = bspFileStructure.lumpDef(lumpIndex);
        ui->lumpListWidget->addItem(lumpDef->name());
    }
}
