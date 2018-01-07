#ifndef DISPLAYSTRINGCONVERSION_H
#define DISPLAYSTRINGCONVERSION_H

#include <QString>
#include <QVariant>

#include "bsp/struct/bspstructitemtypes.h"
#include "bsp/struct/bspstructgenericblock.h"

namespace DisplayStringConversion
{
    enum FormatHint
    {
        NoFormatHint = 0,
        IntegerAsHex = (1 << 0),
    };

    QString toString(const QVariant& variant, BSPStructItemTypes::CoreItemType coreType, quint32 formatHint = NoFormatHint);
    QString typeString(const BSPStructGenericBlock& member);
}

#endif // DISPLAYSTRINGCONVERSION_H
