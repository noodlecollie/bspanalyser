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

QListWidget* BSPLumpViewArea::lumpListWidget()
{
    return ui->lumpListWidget;
}
