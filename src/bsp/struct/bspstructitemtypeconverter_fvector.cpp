#include "bspstructitemtypeconverter_fvector.h"

#include <QVector3D>
#include <QVector4D>

#include "bspstructgenericblock.h"
#include "bspstructitemtypes.h"

#include "bsp/axiallyalignedboundingbox.h"

BSPStructItemTypeConverter_FVector::BSPStructItemTypeConverter_FVector(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

BSPStructItemTypeConverter_FVector::~BSPStructItemTypeConverter_FVector()
{
}

QVariant BSPStructItemTypeConverter_FVector::value(const QByteArray &structData, quint32 index)
{
    switch ( BSPStructItemTypes::unmodifiedCoreType(m_Member.itemType()) )
    {
        case BSPStructItemTypes::Type_FVector3:
        {
            const LocalFVector<3>* vec3 = m_Member.itemPointer<LocalFVector<3>>(structData, index);

            return QVariant(QVector3D(vec3->components[0],
                                      vec3->components[1],
                                      vec3->components[2]));
        }

        case BSPStructItemTypes::Type_FVector4:
        {
            const LocalFVector<4>* vec4 = m_Member.itemPointer<LocalFVector<4>>(structData, index);

            return QVariant(QVector4D(vec4->components[0],
                                      vec4->components[1],
                                      vec4->components[2],
                                      vec4->components[3]));
        }

        case BSPStructItemTypes::Type_FVector3AABB:
        {
            const LocalFVector<6>* aabb = m_Member.itemPointer<LocalFVector<6>>(structData, index);
            QVector3D min(aabb->components[0], aabb->components[1], aabb->components[2]);
            QVector3D max(aabb->components[3], aabb->components[4], aabb->components[5]);

            return QVariant::fromValue<AxiallyAlignedBoundingBox>(AxiallyAlignedBoundingBox(min, max));
        }

        default:
        {
            return QVariant();
        }
    }
}
