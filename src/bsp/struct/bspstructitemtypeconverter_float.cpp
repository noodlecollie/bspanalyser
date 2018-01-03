#include "bspstructitemtypeconverter_float.h"

BSPStructItemTypeConverter_Float::BSPStructItemTypeConverter_Float(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QVariant BSPStructItemTypeConverter_Float::value(const QByteArray &structData, quint32 index)
{
    return QVariant(m_Member.item<float>(structData, index));
}
