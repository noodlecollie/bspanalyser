#include "structmemberconfigreader_simple.h"

StructMemberConfigReader_Simple::StructMemberConfigReader_Simple(BSPStructItemTypes::CoreItemType type,
                                                                 const QSharedPointer<StructLumpDef>& structLumpDef,
                                                                 const JSONReaderItemPtr& memberObject,
                                                                 quint32 count)
    : StructMemberConfigReader(type, structLumpDef, memberObject, count)
{
}

StructMemberConfigReader_Simple::~StructMemberConfigReader_Simple()
{
}

BSPStructGenericBlock* StructMemberConfigReader_Simple::loadAndCreateMember()
{
    return m_pStructLumpDef->bspStruct().addMember(m_nType, m_nCount);
}
