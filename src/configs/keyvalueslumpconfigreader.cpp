#include "keyvalueslumpconfigreader.h"

KeyValuesLumpConfigReader::KeyValuesLumpConfigReader(const QString &lumpName)
    : AbstractLumpConfigReader(lumpName)
{
}

KeyValuesLumpConfigReader::~KeyValuesLumpConfigReader()
{
}

QSharedPointer<BSPLumpDef> KeyValuesLumpConfigReader::createLumpDef()
{
    return BSPLumpDef::createEmptyLumpDef(m_strLumpName, BSPLumpDef::LumpType::Keyvalues);
}

void KeyValuesLumpConfigReader::readLumpDataInternal()
{
}

void KeyValuesLumpConfigReader::linkInternal()
{
}
