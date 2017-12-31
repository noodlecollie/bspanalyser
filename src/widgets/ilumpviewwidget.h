#ifndef ILUMPVIEWWIDGET_H
#define ILUMPVIEWWIDGET_H

#include "bsp/bspdatafragment.h"

class QWidget;

class ILumpViewWidget
{
public:
    virtual ~ILumpViewWidget() {}

    virtual QWidget* asWidget() = 0;
    virtual void loadLumpData(const BSPDataFragment& dataFragment) = 0;
};

#endif // ILUMPVIEWWIDGET_H
