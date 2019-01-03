#ifndef DISPLAYSTRINGCONVERSION_H
#define DISPLAYSTRINGCONVERSION_H

#include <QString>
#include <QVariant>

#include "bsp/struct/bspstructitemtypes.h"
#include "bsp/struct/bspstructgenericblock.h"

class StructLumpDef;

namespace DisplayStringConversion
{
    enum FormatHint
    {
        NoFormatHint = 0,
        IntegerAsHex = (1 << 0),
    };

    QString toString(const QVariant& variant, BSPStructItemTypes::CoreItemType coreType, quint32 formatHint = NoFormatHint);
    QString typeString(const BSPStructGenericBlock& member);

    QString displayStringForMember(const StructLumpDef& lumpDef, const QByteArray& lumpData, quint32 itemIndex, quint32 memberIndex);

    // Assumes that memberData corresponds to what is returned from StructLumpDef::getDataForIndex().
    QString displayStringFromMemberData(const StructLumpDef& lumpDef, const QByteArray& memberData, quint32 memberIndex);

    quint32 formatHintForMember(const BSPStructGenericBlock &member);
}

#endif // DISPLAYSTRINGCONVERSION_H
