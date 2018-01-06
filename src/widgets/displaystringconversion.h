#ifndef DISPLAYSTRINGCONVERSION_H
#define DISPLAYSTRINGCONVERSION_H

#include <QString>
#include <QVariant>

#include "bsp/struct/bspstructitemtypes.h"

namespace DisplayStringConversion
{
    QString toString(const QVariant& variant, BSPStructItemTypes::CoreItemType coreType);
}

#endif // DISPLAYSTRINGCONVERSION_H
