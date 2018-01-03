#include "bspstructitemtypeconverterfactory.h"

#include "bspstructitemtypeconverter_float.h"
#include "bspstructitemtypeconverter_fvector.h"
#include "bspstructitemtypeconverter_integer.h"
#include "bspstructitemtypeconverter_rgb8.h"

namespace BSPStructItemTypeConverterFactory
{
    QSharedPointer<BSPStructItemTypeConverter> createConverter(const BSPStructGenericBlock &member)
    {
        BSPStructItemTypeConverter* converter = nullptr;

        switch ( BSPStructItemTypes::unmodifiedCoreType(member.itemType()) )
        {
            case BSPStructItemTypes::Type_Int8:
            case BSPStructItemTypes::Type_Int16:
            case BSPStructItemTypes::Type_Int32:
            {
                converter = new BSPStructItemTypeConverter_Integer(member);
                break;
            }

            case BSPStructItemTypes::Type_Float:
            {
                converter = new BSPStructItemTypeConverter_Float(member);
                break;
            }

            case BSPStructItemTypes::Type_FVector3:
            case BSPStructItemTypes::Type_FVector4:
            case BSPStructItemTypes::Type_FVector3AABB:
            {
                converter = new BSPStructItemTypeConverter_FVector(member);
                break;
            }

            case BSPStructItemTypes::Type_RGB8:
            {
                converter = new BSPStructItemTypeConverter_RGB8(member);
                break;
            }

            default:
            {
                break;
            }
        }

        return QSharedPointer<BSPStructItemTypeConverter>(converter);
    }
}
