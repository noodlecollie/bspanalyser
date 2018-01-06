#include "displaystringconversion.h"

#include <QCoreApplication>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include "bsp/axiallyalignedboundingbox.h"

namespace DisplayStringConversion
{
    QString toString(const QVariant &variant, BSPStructItemTypes::CoreItemType coreType)
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

            default:
            {
                return variant.toString();
            }
        }
    }
}
