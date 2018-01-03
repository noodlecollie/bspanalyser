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

    BSPStructItemTypes::CoreItemType m_nType;
    QSharedPointer<StructLumpDef> m_pStructLumpDef;
    JSONReaderItemPtr m_pMemberObject;
    quint32 m_nCount;
};

#endif // STRUCTMEMBERCONFIGREADER_H
