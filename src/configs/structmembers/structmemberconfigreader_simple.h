#ifndef STRUCTMEMBERCONFIGREADER_SIMPLE_H
#define STRUCTMEMBERCONFIGREADER_SIMPLE_H

#include "structmemberconfigreader.h"

class StructMemberConfigReader_Simple : public StructMemberConfigReader
{
public:
    StructMemberConfigReader_Simple(BSPStructItemTypes::CoreItemType type,
                                    const QSharedPointer<StructLumpDef>& structLumpDef,
                                    const JSONReaderItemPtr& memberObject,
                                    quint32 count);
    ~StructMemberConfigReader_Simple();

    virtual BSPStructGenericBlock* loadAndCreateMember() override;
};

#endif // STRUCTMEMBERCONFIGREADER_SIMPLE_H
