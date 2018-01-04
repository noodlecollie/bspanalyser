#ifndef STRUCTMEMBERCONFIGREADER_INTEGER_H
#define STRUCTMEMBERCONFIGREADER_INTEGER_H

#include "structmemberconfigreader.h"

class StructMemberConfigReader_Integer : public StructMemberConfigReader
{
public:
    StructMemberConfigReader_Integer(BSPStructItemTypes::CoreItemType type,
                                     const QSharedPointer<StructLumpDef>& structLumpDef,
                                     const JSONReaderItemPtr& memberObject,
                                     quint32 count);
    virtual ~StructMemberConfigReader_Integer();

    virtual BSPStructGenericBlock* loadAndCreateMember() override;
};

#endif // STRUCTMEMBERCONFIGREADER_INTEGER_H
