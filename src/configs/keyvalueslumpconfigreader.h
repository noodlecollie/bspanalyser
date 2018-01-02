#ifndef KEYVALUESLUMPCONFIGREADER_H
#define KEYVALUESLUMPCONFIGREADER_H

#include "abstractlumpconfigreader.h"

class KeyValuesLumpConfigReader : public AbstractLumpConfigReader
{
public:
    KeyValuesLumpConfigReader(const QString& lumpName);
    virtual ~KeyValuesLumpConfigReader();

protected:
    virtual QSharedPointer<BSPLumpDef> createLumpDef() override;
    virtual void readLumpDataInternal() override;
    virtual void linkInternal() override;
};

#endif // KEYVALUESLUMPCONFIGREADER_H
