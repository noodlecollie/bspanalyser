#include "displaystringconversion.h"

#include <QCoreApplication>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

#include "bsp/axiallyalignedboundingbox.h"

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
}
