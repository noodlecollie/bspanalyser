#include "bspstructitemtypeconverter_float.h"

#include "bspstructgenericblock.h"

BSPStructItemTypeConverter_Float::BSPStructItemTypeConverter_Float(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

BSPStructItemTypeConverter_Float::~BSPStructItemTypeConverter_Float()
{
}

QVariant BSPStructItemTypeConverter_Float::value(const QByteArray &structData, quint32 index)
{
    return QVariant(m_Member.item<float>(structData, index));
}
