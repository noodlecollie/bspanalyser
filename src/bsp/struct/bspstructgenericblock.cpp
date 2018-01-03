#include "bspstructgenericblock.h"

BSPStructGenericBlock::BSPStructGenericBlock(quint32 inOffset, BSPStructItemTypes::CoreItemType inType, quint32 inItemCount)
    : m_nOffsetInStruct(inOffset),
      m_nItemType(inType),
      m_nItemCount(inItemCount)
{

}

quint32 BSPStructGenericBlock::offset() const
{
    return m_nOffsetInStruct;
}

BSPStructItemTypes::CoreItemType BSPStructGenericBlock::itemType() const
{
    return m_nItemType;
}

quint32 BSPStructGenericBlock::itemSize() const
{
    return BSPStructItemTypes::sizeOfCoreType(m_nItemType);
}

quint32 BSPStructGenericBlock::itemCount() const
{
    return m_nItemCount;
}

quint32 BSPStructGenericBlock::totalSize() const
{
    return itemCount() * itemSize();
}
