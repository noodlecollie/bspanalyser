#include "bspstructitemtypes.h"

quint32 BSPStructItemTypes::sizeOfCoreType(CoreItemType type)
{
    switch (unmodifiedCoreType(type))
    {
        case Type_Int8:
        {
            return sizeof(qint8);
        }

        case Type_Int16:
        {
            return sizeof(qint16);
        }

        case Type_Int32:
        {
            return sizeof(qint32);
        }

        case Type_Float:
        {
            return sizeof(float);
        }

        case Type_FVector3:
        {
            return 3 * sizeof(float);
        }

        case Type_FVector4:
        {
            return 4 * sizeof(float);
        }

        case Type_RGB8:
        {
            return 3 * sizeof(qint8);
        }

        case Type_FVector3AABB:
        {
            return 2 * 3 * sizeof(float);
        }

        default:
        {
            return 0;
        }
    }
}
