#ifndef STRUCTLUMPCONFIGREADER_H
#define STRUCTLUMPCONFIGREADER_H

#include "abstractlumpconfigreader.h"

#include "bsp/structlumpdef.h"
#include "bsp/struct/bspstructitemtypes.h"

class StructLumpConfigReader : public AbstractLumpConfigReader
{
public:
    StructLumpConfigReader(const QString& lumpName);
    virtual ~StructLumpConfigReader();

protected:
    virtual QSharedPointer<BSPLumpDef> createLumpDef() override;
    virtual void readLumpDataInternal() override;
    virtual void linkInternal() override;

private:
    void readMember(const JSONReaderItemPtr& memberObject);
    BSPStructItemTypes::PublicItemType getPublicType(const JSONReaderItemPtr& memberObject, const QString& key);

    QSharedPointer<StructLumpDef> m_pStructLumpDef;
};

#endif // STRUCTLUMPCONFIGREADER_H
