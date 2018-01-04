#include "bspstructitemtypeconverter_integer.h"

#include "bspstructitemtypes.h"
#include "bspstructgenericblock.h"

BSPStructItemTypeConverter_Integer::BSPStructItemTypeConverter_Integer(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

BSPStructItemTypeConverter_Integer::~BSPStructItemTypeConverter_Integer()
{
}

QVariant BSPStructItemTypeConverter_Integer::value(const QByteArray &structData, quint32 index)
{
    SignedUnsignedInt32 intermediateValue;
    intermediateValue.signedVal = 0;

    switch ( BSPStructItemTypes::unmodifiedCoreType(m_Member.itemType()) )
    {
        case BSPStructItemTypes::Type_Int8:
        {
            intermediateValue.signedVal = m_Member.item<qint8>(structData, index);
            break;
        }

        case BSPStructItemTypes::Type_Int16:
        {
            intermediateValue.signedVal = m_Member.item<qint16>(structData, index);
            break;
        }

        case BSPStructItemTypes::Type_Int32:
        {
            intermediateValue.signedVal = m_Member.item<qint32>(structData, index);
            break;
        }

        default:
        {
            return QString();
        }
    }

    if ( BSPStructItemTypes::coreTypeHasModifier(m_Member.itemType(), BSPStructItemTypes::Mod_IsUnsigned) )
    {
        return QVariant(intermediateValue.unsignedVal);
    }
    else
    {
        return QVariant(intermediateValue.signedVal);
    }
}
