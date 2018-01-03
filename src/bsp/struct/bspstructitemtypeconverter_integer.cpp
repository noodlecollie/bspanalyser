#include "bspstructitemtypeconverter_integer.h"

BSPStructItemTypeConverter_Integer::BSPStructItemTypeConverter_Integer(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QString BSPStructItemTypeConverter_Integer::toString(const QByteArray &structData, quint32 index)
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

    if ( BSPStructItemTypes::coreTypeIsUnsigned(m_Member.itemType()) )
    {
        return QString::number(intermediateValue.unsignedVal);
    }
    else
    {
        return QString::number(intermediateValue.signedVal);
    }
}
