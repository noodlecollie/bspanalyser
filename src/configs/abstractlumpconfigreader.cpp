#include "abstractlumpconfigreader.h"

#include "visibilitylumpconfigreader.h"
#include "keyvalueslumpconfigreader.h"
#include "structlumpconfigreader.h"

AbstractLumpConfigReader::AbstractLumpConfigReader()
    : m_strLumpName(),
      m_pLumpItemsObject(),
      m_pBspFileStructure(nullptr),
      m_pLumpDef()
{
}

AbstractLumpConfigReader::AbstractLumpConfigReader(const QString &lumpName)
    : m_strLumpName(lumpName),
      m_pLumpItemsObject(),
      m_pBspFileStructure(nullptr),
      m_pLumpDef()
{
}

AbstractLumpConfigReader::~AbstractLumpConfigReader()
{
}

QSharedPointer<AbstractLumpConfigReader> AbstractLumpConfigReader::createReader(const QString &lumpName, BSPLumpDef::LumpType type)
{
    switch (type)
    {
        case BSPLumpDef::LumpType::Keyvalues:
        {
            return QSharedPointer<AbstractLumpConfigReader>(new KeyValuesLumpConfigReader(lumpName));
        }

        case BSPLumpDef::LumpType::Struct:
        {
            return QSharedPointer<AbstractLumpConfigReader>(new StructLumpConfigReader(lumpName));
        }

        case BSPLumpDef::LumpType::VisData:
        {
            return QSharedPointer<AbstractLumpConfigReader>(new VisibilityLumpConfigReader(lumpName));
        }

        default:
        {
            return QSharedPointer<AbstractLumpConfigReader>();
        }
    }
}

void AbstractLumpConfigReader::setLumpItemsObject(const JSONReaderItemPtr &object)
{
    m_pLumpItemsObject = object;
}

void AbstractLumpConfigReader::setBspFileStructure(BSPFileStructure *file)
{
    m_pBspFileStructure = file;
}

bool AbstractLumpConfigReader::isValid() const
{
    return m_pBspFileStructure && m_pLumpItemsObject && !m_strLumpName.isEmpty();
}

void AbstractLumpConfigReader::readLumpData()
{
    if ( !isValid() )
    {
        return;
    }

    m_pLumpDef = createLumpDef();
    if ( !m_pLumpDef )
    {
        return;
    }

    readLumpDataInternal();
}

void AbstractLumpConfigReader::link()
{
    if ( !isValid() || !m_pLumpDef )
    {
        return;
    }

    linkInternal();
}

QSharedPointer<BSPLumpDef> AbstractLumpConfigReader::lumpDef() const
{
    return m_pLumpDef;
}

JSONReaderItemPtr AbstractLumpConfigReader::getLumpItemObject() const
{
    return m_pLumpItemsObject->getObjectItem(m_strLumpName, QJsonValue::Object);
}
