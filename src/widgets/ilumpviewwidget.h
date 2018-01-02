#ifndef ILUMPVIEWWIDGET_H
#define ILUMPVIEWWIDGET_H

#include <QSharedPointer>

#include "bsp/bspdatafragment.h"
#include "bsp/bsplumpdef.h"

class QWidget;

class ILumpViewWidget
{
public:
    virtual ~ILumpViewWidget() {}

    virtual QWidget* asWidget() = 0;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef>& lumpDef, const BSPDataFragment& fragment) = 0;
};

#endif // ILUMPVIEWWIDGET_H
