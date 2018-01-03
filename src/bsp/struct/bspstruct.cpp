#include "bspstruct.h"

BSPStruct::BSPStruct(QObject *parent)
    : QObject(parent),
      m_liMembers()
{
}

BSPStruct::~BSPStruct()
{
    qDeleteAll(m_liMembers);
}

void BSPStruct::addMember(BSPStructItemTypes::CoreItemType type, quint32 count)
{
    quint32 currentOffset = 0;

    if ( !m_liMembers.isEmpty() )
    {
        BSPStructGenericBlock* lastMember = m_liMembers.last();
        currentOffset = lastMember->offset() + lastMember->totalSize();
    }

    m_liMembers.append(new BSPStructGenericBlock(currentOffset, BSPStructItemTypes::sizeOfCoreType(type), count));
}
