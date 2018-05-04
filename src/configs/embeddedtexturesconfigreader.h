#ifndef EMBEDDEDTEXTURESCONFIGREADER_H
#define EMBEDDEDTEXTURESCONFIGREADER_H

#include "abstractlumpconfigreader.h"

class EmbeddedTexturesConfigReader : public AbstractLumpConfigReader
{
public:
    EmbeddedTexturesConfigReader(const QString& lumpName);
    virtual ~EmbeddedTexturesConfigReader();

protected:
    virtual QSharedPointer<BSPLumpDef> createLumpDef() override;
    virtual void readLumpDataInternal() override;
    virtual void linkInternal() override;
};

#endif // EMBEDDEDTEXTURESCONFIGREADER_H
