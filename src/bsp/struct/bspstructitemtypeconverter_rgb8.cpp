#include "bspstructitemtypeconverter_rgb8.h"

BSPStructItemTypeConverter_RGB8::BSPStructItemTypeConverter_RGB8(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QString BSPStructItemTypeConverter_RGB8::toString(const QByteArray &structData, quint32 index)
{
    const LocalRGB8* rgb8 = m_Member.itemPointer<LocalRGB8>(structData, index);

    return QString("(%0 %1 %2)")
            .arg(rgb8->colour[0])
            .arg(rgb8->colour[1])
            .arg(rgb8->colour[2]);
}
