#include "bspstructitemtypeconverter_fvector.h"

BSPStructItemTypeConverter_FVector::BSPStructItemTypeConverter_FVector(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QString BSPStructItemTypeConverter_FVector::toString(const QByteArray &structData, quint32 index)
{
    switch ( BSPStructItemTypes::unmodifiedCoreType(m_Member.itemType()) )
    {
        case BSPStructItemTypes::Type_FVector3:
        {
            const LocalFVector<3>* vec3 = m_Member.itemPointer<LocalFVector<3>>(structData, index);

            return QString("[%0 %1 %2]")
                    .arg(vec3->components[0])
                    .arg(vec3->components[1])
                    .arg(vec3->components[2]);
        }

        case BSPStructItemTypes::Type_FVector4:
        {
            const LocalFVector<4>* vec4 = m_Member.itemPointer<LocalFVector<4>>(structData, index);

            return QString("[%0 %1 %2 %3]")
                    .arg(vec4->components[0])
                    .arg(vec4->components[1])
                    .arg(vec4->components[2])
                    .arg(vec4->components[3]);
        }

        case BSPStructItemTypes::Type_FVector3AABB:
        {
            const LocalFVector<6>* aabb = m_Member.itemPointer<LocalFVector<6>>(structData, index);

            return QString("[%0 %1 %2] - [%3 %4 %5]")
                    .arg(aabb->components[0])
                    .arg(aabb->components[1])
                    .arg(aabb->components[2])
                    .arg(aabb->components[3])
                    .arg(aabb->components[4])
                    .arg(aabb->components[5]);
        }

        default:
        {
            return QString();
        }
    }
}
