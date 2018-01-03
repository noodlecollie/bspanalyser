#include "bspstructitemtypeconverter_rgb8.h"

#include <QColor>

BSPStructItemTypeConverter_RGB8::BSPStructItemTypeConverter_RGB8(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

QVariant BSPStructItemTypeConverter_RGB8::value(const QByteArray &structData, quint32 index)
{
    const LocalRGB8* rgb8 = m_Member.itemPointer<LocalRGB8>(structData, index);
    return QVariant(QColor(rgb8->colour[0], rgb8->colour[1], rgb8->colour[2], 255));
}
