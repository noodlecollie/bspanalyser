#ifndef VISIBILITYLUMPDEF_H
#define VISIBILITYLUMPDEF_H

#include <QSharedPointer>

#include "structlumpdef.h"

class VisibilityLumpDef : public BSPLumpDef
{
public:
    VisibilityLumpDef();

    bool isCompressed() const;
    void setIsCompressed(bool compressed);

    QSharedPointer<StructLumpDef> leavesLump() const;
    void setLeavesLump(const QSharedPointer<StructLumpDef>& lump);

private:
    bool m_bCompressed;
    QSharedPointer<StructLumpDef> m_pLeavesLump;
};

#endif // VISIBILITYLUMPDEF_H
