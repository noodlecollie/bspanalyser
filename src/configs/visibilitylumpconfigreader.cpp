#include "visibilitylumpconfigreader.h"

VisibilityLumpConfigReader::VisibilityLumpConfigReader(const QString& lumpName)
    : AbstractLumpConfigReader(lumpName),
      m_pVisibilityLumpDef()
{
}

VisibilityLumpConfigReader::~VisibilityLumpConfigReader()
{
}

QSharedPointer<BSPLumpDef> VisibilityLumpConfigReader::createLumpDef()
{
    QSharedPointer<BSPLumpDef> lump = BSPLumpDef::createEmptyLumpDef(m_strLumpName, BSPLumpDef::LumpType::VisData);
    m_pVisibilityLumpDef = lump.staticCast<VisibilityLumpDef>();
    return lump;
}

void VisibilityLumpConfigReader::readLumpDataInternal()
{
    JSONReaderItemPtr lumpItem = getLumpItemObject();
    m_pVisibilityLumpDef->setIsCompressed(lumpItem->getObjectItemOfType<bool>("rle"));
}

void VisibilityLumpConfigReader::linkInternal()
{
    JSONReaderItemPtr lumpItem = getLumpItemObject();
    QString leavesLumpName = lumpItem->getObjectItemOfType<QString>("leaveslump");
    QSharedPointer<BSPLumpDef> leavesLumpDef = m_pBspFileStructure->lumpDef(leavesLumpName);

    if ( !leavesLumpDef )
    {
        throw GenericException(QString("Visibility lump '%0' references leaves lump '%1' which was not found.")
                               .arg(m_strLumpName)
                               .arg(leavesLumpName));
    }

    if ( leavesLumpDef->type() != BSPLumpDef::LumpType::Struct )
    {
        throw GenericException(QString("Visibility lump '%0' references leaves lump '%1' "
                                       "which was of type '%2', not '%3'.")
                               .arg(m_strLumpName)
                               .arg(leavesLumpName)
                               .arg(BSPLumpDef::lumpTypeNameMap().key(leavesLumpDef->type()))
                               .arg(BSPLumpDef::lumpTypeNameMap().key(BSPLumpDef::LumpType::Struct)));
    }

    m_pVisibilityLumpDef->setLeavesLump(leavesLumpDef.staticCast<StructLumpDef>());
}
