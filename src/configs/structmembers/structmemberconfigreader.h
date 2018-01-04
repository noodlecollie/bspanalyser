#ifndef STRUCTMEMBERCONFIGREADER_H
#define STRUCTMEMBERCONFIGREADER_H

#include <QSharedPointer>

#include "configs/jsonreaderitem.h"
#include "bsp/structlumpdef.h"
#include "bsp/struct/bspstructgenericblock.h"

class StructMemberConfigReader
{
public:
    virtual ~StructMemberConfigReader();

    virtual BSPStructGenericBlock* loadAndCreateMember() = 0;

protected:
    StructMemberConfigReader(BSPStructItemTypes::CoreItemType type,
                             const QSharedPointer<StructLumpDef>& structLumpDef,
                             const JSONReaderItemPtr& memberObject,
                             quint32 count);

    template<typename T>
    void setAttributeIfExists(BSPStructGenericBlock* member, BSPStructItemAttributes::Attribute attribute)
    {
        QString attributeName = BSPStructItemAttributes::attributeNameMap().key(attribute).toLower();

        if ( (*m_pMemberObject)->toObject().contains(attributeName) )
        {
            member->attributes().setAttributeValue(attribute, QVariant::fromValue<T>(m_pMemberObject->getObjectItemOfType<T>(attributeName)));
        }
    }

    BSPStructItemTypes::CoreItemType m_nType;
    QSharedPointer<StructLumpDef> m_pStructLumpDef;
    JSONReaderItemPtr m_pMemberObject;
    quint32 m_nCount;
};

#endif // STRUCTMEMBERCONFIGREADER_H
