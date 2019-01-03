#include "structlumpdef.h"

StructLumpDef::StructLumpDef()
    : BSPLumpDef(),
      m_Struct()
{

}

BSPStruct& StructLumpDef::bspStruct()
{
    return m_Struct;
}

QByteArray StructLumpDef::getDataForItem(const QByteArray &lumpData, quint32 item) const
{
    if ( lumpData.isEmpty() )
    {
        return QByteArray();
    }

    quint32 structSize = m_Struct.size();
    quint32 endOfRequestedItem = (item + 1) * structSize;

    if ( endOfRequestedItem > static_cast<quint32>(lumpData.count()) )
    {
        return QByteArray();
    }

    return lumpData.mid(item * structSize, structSize);
}
