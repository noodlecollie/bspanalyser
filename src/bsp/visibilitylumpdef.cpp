#include "visibilitylumpdef.h"

VisibilityLumpDef::VisibilityLumpDef()
    : BSPLumpDef(),
      m_bCompressed(false),
      m_pLeavesLump()
{

}

bool VisibilityLumpDef::isCompressed() const
{
    return m_bCompressed;
}

void VisibilityLumpDef::setIsCompressed(bool compressed)
{
    m_bCompressed = compressed;
}

QSharedPointer<StructLumpDef> VisibilityLumpDef::leavesLump() const
{
    return m_pLeavesLump;
}

void VisibilityLumpDef::setLeavesLump(const QSharedPointer<StructLumpDef> &lump)
{
    m_pLeavesLump = lump;
}
