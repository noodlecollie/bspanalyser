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

void BSPStruct::clear()
{
    qDeleteAll(m_liMembers);
    m_liMembers.clear();
}
