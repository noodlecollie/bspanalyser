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
    bool referencesEnum = (*m_pMemberObject)->toObject().contains("enum");
    if ( referencesEnum )
    {
        QString referencedEnum = m_pMemberObject->getObjectItemOfType<QString>("enum");

        // TODO: Work out how to set up enums.
        Q_UNUSED(referencedEnum);
    }

    return m_pStructLumpDef->bspStruct().addMember(m_nType, m_nCount);
}
