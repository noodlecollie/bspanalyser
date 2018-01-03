#include "structmemberconfigreader.h"

StructMemberConfigReader::StructMemberConfigReader(BSPStructItemTypes::CoreItemType type,
                                                   const QSharedPointer<StructLumpDef>& structLumpDef,
                                                   const JSONReaderItemPtr& memberObject,
                                                   quint32 count)
    : m_nType(type),
      m_pStructLumpDef(structLumpDef),
      m_pMemberObject(memberObject),
      m_nCount(count)
{
}

StructMemberConfigReader::~StructMemberConfigReader()
{
}
