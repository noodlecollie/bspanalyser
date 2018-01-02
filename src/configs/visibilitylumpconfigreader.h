#ifndef VISIBILITYLUMPCONFIGREADER_H
#define VISIBILITYLUMPCONFIGREADER_H

#include "abstractlumpconfigreader.h"

#include "bsp/visibilitylumpdef.h"

class VisibilityLumpConfigReader : public AbstractLumpConfigReader
{
public:
    VisibilityLumpConfigReader(const QString& lumpName);
    virtual ~VisibilityLumpConfigReader();

protected:
    virtual QSharedPointer<BSPLumpDef> createLumpDef() override;
    virtual void readLumpDataInternal() override;
    virtual void linkInternal() override;

private:
    JSONReaderItemPtr getLumpItemObject() const;

    QSharedPointer<VisibilityLumpDef> m_pVisibilityLumpDef;
};

#endif // VISIBILITYLUMPCONFIGREADER_H
