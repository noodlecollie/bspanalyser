#include "structlumpdef.h"
#include "exceptions/genericexception.h"

StructLumpDef::StructLumpDef()
    : BSPLumpDef(),
      m_Struct()
{

}

BSPStruct& StructLumpDef::bspStruct()
{
    return m_Struct;
}

const BSPStruct& StructLumpDef::bspStruct() const
{
    return m_Struct;
}

QByteArray StructLumpDef::getDataForIndex(const QByteArray &lumpData, quint32 index) const
{
    if ( lumpData.isEmpty() )
    {
        throw GenericException("Lump data was empty.");
    }

    quint32 structSize = m_Struct.size();
    quint32 endOfRequestedItem = (index + 1) * structSize;

    if ( endOfRequestedItem > static_cast<quint32>(lumpData.count()) )
    {
        throw GenericException(QString("Range of requested item %0 (offset %1, length %2 bytes) was out of range of lump data (%3 bytes).")
                               .arg(index)
                               .arg(index * structSize)
                               .arg(structSize)
                               .arg(lumpData.count()));
    }

    return lumpData.mid(static_cast<int>(index * structSize), static_cast<int>(structSize));
}
