#ifndef STRUCTLUMPCONFIGREADER_H
#define STRUCTLUMPCONFIGREADER_H

#include "abstractlumpconfigreader.h"

#include "bsp/structlumpdef.h"

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
    QSharedPointer<StructLumpDef> m_pStructLumpDef;
};

#endif // STRUCTLUMPCONFIGREADER_H
