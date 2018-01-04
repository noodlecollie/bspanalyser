#include "bspstruct.h"

BSPStruct::BSPStruct()
    : m_liMembers()
{
}

BSPStruct::~BSPStruct()
{
    clear();
}

BSPStructGenericBlock* BSPStruct::addMember(BSPStructItemTypes::CoreItemType type, quint32 count)
{
    if ( BSPStructItemTypes::sizeOfCoreType(type) < 1 || count < 1 )
    {
        return nullptr;
    }

    quint32 currentOffset = 0;

    if ( !m_liMembers.isEmpty() )
    {
        BSPStructGenericBlock* lastMember = m_liMembers.last();
        currentOffset = lastMember->offset() + lastMember->totalSize();
    }

    BSPStructGenericBlock* member = new BSPStructGenericBlock(currentOffset, type, count);
    m_liMembers.append(member);
    return member;
}

BSPStructGenericBlock* BSPStruct::member(int index) const
{
    return m_liMembers.at(index);
}

void BSPStruct::clear()
{
    qDeleteAll(m_liMembers);
    m_liMembers.clear();
}

int BSPStruct::memberCount() const
{
    return m_liMembers.count();
}

quint32 BSPStruct::size() const
{
    quint32 outSize = 0;

    for ( BSPStructGenericBlock* member : m_liMembers )
    {
        outSize += member->totalSize();
    }

    return outSize;
}
