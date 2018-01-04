#include "bspstructitemtypeconverter_string.h"

#include "bspstructgenericblock.h"

BSPStructItemTypeConverter_String::BSPStructItemTypeConverter_String(const BSPStructGenericBlock &member)
    : BSPStructItemTypeConverter(member)
{
}

BSPStructItemTypeConverter_String::~BSPStructItemTypeConverter_String()
{
}

QVariant BSPStructItemTypeConverter_String::value(const QByteArray &structData, quint32 index)
{
    // Copy into intermediate buffer, just in case string value in struct data is not null-terminated.
    QByteArray intermediateString(m_Member.itemCount() + 1, 0);

    if ( index < m_Member.itemCount() )
    {
        const char* stringData = m_Member.itemPointer<char>(structData, index);
        memcpy(intermediateString.data(), stringData, m_Member.itemCount() - index);
    }

    return QVariant(intermediateString.constData());
}
