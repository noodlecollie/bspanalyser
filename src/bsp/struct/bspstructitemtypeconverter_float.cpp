#include "bspstructitemtypeconverter_float.h"

BSPStructItemTypeConverter_Float::BSPStructItemTypeConverter_Float(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QString BSPStructItemTypeConverter_Float::toString(const QByteArray &structData, quint32 index)
{
    return QString::number(m_Member.item<float>(structData, index));
}
