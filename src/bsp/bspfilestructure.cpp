#include "bspfilestructure.h"

BSPFileStructure::BSPFileStructure()
    : m_nVersion(0),
      m_liLumpDefs()
{

}

quint32 BSPFileStructure::version() const
{
    return m_nVersion;
}

void BSPFileStructure::setVersion(quint32 newVersion)
{
    m_nVersion = newVersion;
}

void BSPFileStructure::addLumpDef(const QSharedPointer<BSPLumpDef>& lump)
{
    if ( !lump )
    {
        return;
    }

    lump->setIndex(m_liLumpDefs.count());
    m_liLumpDefs.append(lump);
}

int BSPFileStructure::lumpDefCount() const
{
    return m_liLumpDefs.count();
}

void BSPFileStructure::clearLumpDefs()
{
    m_liLumpDefs.clear();
}

QSharedPointer<BSPLumpDef> BSPFileStructure::lumpDef(int index) const
{
    return m_liLumpDefs.at(index);
}
