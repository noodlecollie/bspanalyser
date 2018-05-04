#include "embeddedtexturesconfigreader.h"

EmbeddedTexturesConfigReader::EmbeddedTexturesConfigReader(const QString &lumpName)
    : AbstractLumpConfigReader(lumpName)
{
}

EmbeddedTexturesConfigReader::~EmbeddedTexturesConfigReader()
{
}

QSharedPointer<BSPLumpDef> EmbeddedTexturesConfigReader::createLumpDef()
{
    return BSPLumpDef::createEmptyLumpDef(m_strLumpName, BSPLumpDef::LumpType::EmbeddedTextures);
}

void EmbeddedTexturesConfigReader::readLumpDataInternal()
{
}

void EmbeddedTexturesConfigReader::linkInternal()
{
}
