#include "bspstructgenericblock.h"

BSPStructGenericBlock::BSPStructGenericBlock(quint32 inOffset, quint32 inItemSize, quint32 inItemCount)
    : m_nOffsetInStruct(inOffset),
      m_nItemSize(inItemSize),
      m_nItemCount(inItemCount)
{

}

quint32 BSPStructGenericBlock::offset() const
{
    return m_nOffsetInStruct;
}

void BSPStructGenericBlock::setOffset(quint32 newOffset)
{
    m_nOffsetInStruct = newOffset;
}

quint32 BSPStructGenericBlock::itemSize() const
{
    return m_nItemSize;
}

void BSPStructGenericBlock::setItemSize(quint32 newSize)
{
    m_nItemSize = newSize;
}

quint32 BSPStructGenericBlock::itemCount() const
{
    return m_nItemCount;
}

void BSPStructGenericBlock::setItemCount(quint32 newCount)
{
    m_nItemCount = newCount;
}

quint32 BSPStructGenericBlock::totalSize() const
{
    return itemCount() * itemSize();
}
