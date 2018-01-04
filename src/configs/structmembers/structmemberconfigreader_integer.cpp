#include "structmemberconfigreader_integer.h"

StructMemberConfigReader_Integer::StructMemberConfigReader_Integer(BSPStructItemTypes::CoreItemType type,
                                                                   const QSharedPointer<StructLumpDef>& structLumpDef,
                                                                   const JSONReaderItemPtr& memberObject,
                                                                   quint32 count)
    : StructMemberConfigReader(type, structLumpDef, memberObject, count)
{
}

StructMemberConfigReader_Integer::~StructMemberConfigReader_Integer()
{
}

BSPStructGenericBlock* StructMemberConfigReader_Integer::loadAndCreateMember()
{
    BSPStructGenericBlock* member = m_pStructLumpDef->bspStruct().addMember(m_nType, m_nCount);

    setAttributeIfExists<QString>(member, BSPStructItemAttributes::Attribute::Enum);
    setAttributeIfExists<bool>(member, BSPStructItemAttributes::Attribute::DisplayHex);

    return member;
}
