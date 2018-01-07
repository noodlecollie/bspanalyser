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
    void checkForArrayType(const JSONReaderItemPtr &memberObject);
    BSPStructItemTypes::PublicItemType getPublicType(const JSONReaderItemPtr& memberObject, const QString& key);

    QSharedPointer<StructLumpDef> m_pStructLumpDef;
    BSPStructItemTypes::CoreItemType m_nCurrentCoreType;
    BSPStructItemTypes::PublicItemType m_nCurrentPublicType;
    qint32 m_nCurrentItemCount;
};

#endif // STRUCTLUMPCONFIGREADER_H
