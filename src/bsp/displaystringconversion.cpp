#include "displaystringconversion.h"

#include <QCoreApplication>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

#include "bsp/axiallyalignedboundingbox.h"
#include "bsp/structlumpdef.h"
#include "exceptions/genericexception.h"

namespace DisplayStringConversion
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
    QString toString(const QVariant &variant, BSPStructItemTypes::CoreItemType coreType, quint32 formatHint)
    {
        switch ( BSPStructItemTypes::unmodifiedCoreType(coreType) )
        {
            case BSPStructItemTypes::Type_FVector3:
            {
                QVector3D vec = variant.value<QVector3D>();
                return QString("%0 %1 %2").arg(vec.x()).arg(vec.y()).arg(vec.z());
            }

            case BSPStructItemTypes::Type_FVector4:
            {
                QVector4D vec = variant.value<QVector4D>();
                return QString("%0 %1 %2 %3").arg(vec.x()).arg(vec.y()).arg(vec.z()).arg(vec.w());
            }

            case BSPStructItemTypes::Type_FVector3AABB:
            {
                AxiallyAlignedBoundingBox bbox = variant.value<AxiallyAlignedBoundingBox>();
                QVector3D min = bbox.min();
                QVector3D max = bbox.max();

                return QCoreApplication::translate("DisplayStringConversion", "Min: %0 %1 %2; Max: %3 %4 %5")
                        .arg(min.x())
                        .arg(min.y())
                        .arg(min.z())
                        .arg(max.x())
                        .arg(max.y())
                        .arg(max.z());
            }

            case BSPStructItemTypes::Type_RGB8:
            {
                QColor col = variant.value<QColor>();
                return QString("%0 %1 %2").arg(col.red()).arg(col.green()).arg(col.blue());
            }

            case BSPStructItemTypes::Type_Int8:
            {
                if ( BSPStructItemTypes::coreTypeHasModifier(coreType, BSPStructItemTypes::Mod_InterpretAsString) )
                {
                    return variant.toString();
                }

                // Deliberate fall-through
            }
            case BSPStructItemTypes::Type_Int16:
            case BSPStructItemTypes::Type_Int32:
            {
                if ( formatHint & DisplayStringConversion::IntegerAsHex )
                {
                    bool success = false;
                    quint32 value = static_cast<quint32>(variant.toInt(&success));

                    if ( !success )
                    {
                        return QString();
                    }

                    return "0x" + QString::number(value, 16);
                }
                else
                {
                    return variant.toString();
                }
            }

            default:
            {
                return variant.toString();
            }
        }
    }
#pragma GCC diagnostic pop

    QString typeString(const BSPStructGenericBlock &member)
    {
        QString typeString = BSPStructItemTypes::publicItemTypeNameMap().key(member.publicItemType());

        if ( member.itemCount() > 1 )
        {
            typeString += QString(" [%0]").arg(member.itemCount());
        }

        return typeString;
    }

    QString displayStringForMember(const StructLumpDef& lumpDef, const QByteArray& lumpData, quint32 itemIndex, quint32 memberIndex)
    {
        return displayStringFromMemberData(lumpDef, lumpDef.getDataForIndex(lumpData, itemIndex), memberIndex);
    }

    QString displayStringFromMemberData(const StructLumpDef& lumpDef, const QByteArray& memberData, quint32 memberIndex)
    {
        BSPStructGenericBlock* member = lumpDef.bspStruct().member(static_cast<int>(memberIndex));

        if ( !member )
        {
            throw GenericException(QString("Invalid member at index %0.").arg(memberIndex));
        }

        QSharedPointer<BSPStructItemTypeConverter> typeConverter = member->typeConverter();

        if ( !typeConverter )
        {
            throw GenericException(QString("No type converter present for member '%0' at index %1.").arg(member->name()).arg(memberIndex));
        }

        BSPStructItemTypes::CoreItemType coreType = member->itemType();

        if ( member->itemCount() > 1 && !BSPStructItemTypes::coreTypeHasModifier(coreType, BSPStructItemTypes::Mod_InterpretAsString) )
        {
            QStringList list;

            for ( quint32 itemIndex = 0; itemIndex < member->itemCount(); ++itemIndex )
            {
                list.append(DisplayStringConversion::toString(typeConverter->value(memberData, itemIndex),
                                                              coreType,
                                                              formatHintForMember(*member)));
            }

            return list.join(", ");
        }
        else
        {
            return DisplayStringConversion::toString(typeConverter->value(memberData, 0),
                                                     coreType,
                                                     formatHintForMember(*member));
        }
    }

    quint32 formatHintForMember(const BSPStructGenericBlock &member)
    {
        quint32 formatHint = DisplayStringConversion::NoFormatHint;

        if ( BSPStructItemTypes::coreTypeHasModifier(member.itemType(), BSPStructItemTypes::Mod_IsPrimaryOffset) )
        {
            formatHint |= DisplayStringConversion::IntegerAsHex;
        }
        else
        {
            QVariant hexVariant = member.attributes().attributeValue(BSPStructItemAttributes::Attribute::DisplayHex);
            if ( hexVariant.type() == QVariant::Bool && hexVariant.toBool() )
            {
                formatHint |= DisplayStringConversion::IntegerAsHex;
            }
        }

        return formatHint;
    }
}
