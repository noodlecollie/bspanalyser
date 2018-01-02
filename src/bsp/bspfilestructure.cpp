#include "bspfilestructure.h"

BSPFileStructure::BSPFileStructure()
    : m_nVersion(0),
      m_liLumpDefs()
{

}

void BSPFileStructure::clear()
{
    m_nVersion = 0;
    clearLumpDefs();
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

QSharedPointer<BSPLumpDef> BSPFileStructure::lumpDef(const QString &name) const
{
    for ( int index = 0; index < m_liLumpDefs.count(); ++index )
    {
        QSharedPointer<BSPLumpDef> lump = m_liLumpDefs.at(index);
        if ( lump && lump->name() == name )
        {
            return lump;
        }
    }

    return QSharedPointer<BSPLumpDef>();
}
