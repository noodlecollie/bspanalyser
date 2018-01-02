#include "structlumpconfigreader.h"

StructLumpConfigReader::StructLumpConfigReader(const QString &lumpName)
    : AbstractLumpConfigReader(lumpName)
{
}

StructLumpConfigReader::~StructLumpConfigReader()
{
}

QSharedPointer<BSPLumpDef> StructLumpConfigReader::createLumpDef()
{
    QSharedPointer<BSPLumpDef> lump = BSPLumpDef::createEmptyLumpDef(m_strLumpName, BSPLumpDef::LumpType::Struct);
    m_pStructLumpDef = lump.staticCast<StructLumpDef>();
    return lump;
}

void StructLumpConfigReader::readLumpDataInternal()
{
    // TODO
}

void StructLumpConfigReader::linkInternal()
{
    // TODO
}
