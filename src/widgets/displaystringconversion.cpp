#include "displaystringconversion.h"

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include "bsp/axiallyalignedboundingbox.h"

namespace DisplayStringConversion
{
    QString toString(const QVariant &variant)
    {
        int type = variant.type();

        switch ( type )
        {
            case QMetaType::QVector2D:
            {
                QVector2D vec = variant.value<QVector2D>();
                return QString("(%0 %1)").arg(vec.x()).arg(vec.y());
            }

            case QMetaType::QVector3D:
            {
                QVector3D vec = variant.value<QVector3D>();
                return QString("(%0 %1 %2)").arg(vec.x()).arg(vec.y()).arg(vec.z());
            }

            case QMetaType::QVector4D:
            {
                QVector4D vec = variant.value<QVector4D>();
                return QString("(%0 %1 %2 %3)").arg(vec.x()).arg(vec.y()).arg(vec.z()).arg(vec.w());
            }

            default:
            {
                // Don't go through all the rest of the checks
                // if we know it's not a user type.
                if ( type < QVariant::UserType )
                {
                    return variant.toString();
                }

                // Deliberate fall-through
            }
        }

        if ( type == AxiallyAlignedBoundingBox::metaTypeId() )
        {
            AxiallyAlignedBoundingBox bbox = variant.value<AxiallyAlignedBoundingBox>();
            QVector3D min = bbox.min();
            QVector3D max = bbox.max();

            return QString("(%0 %1 %2) - (%3 %4 %5)")
                    .arg(min.x())
                    .arg(min.y())
                    .arg(min.z())
                    .arg(max.x())
                    .arg(max.y())
                    .arg(max.z());
        }

        // Nothing else left to try.
        return variant.toString();
    }
}
