#include "bspfilestructure.h"

BSPFileStructure::BSPFileStructure()
    : m_liLumpDefs(),
      m_nVersion(0)
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
