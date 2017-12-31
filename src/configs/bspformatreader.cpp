#include "bspformatreader.h"

#include "exceptions/genericexception.h"
#include "jsonreaderutil.h"

BSPFormatReader::BSPFormatReader()
    : m_pCurrentFile(nullptr)
{

}

quint32 BSPFormatReader::readVersion(const QJsonDocument& document, QString& error)
{
    quint32 version = 0;

    try
    {
        version = readVersionInternal(document);
    }
    catch (GenericException& exception)
    {
        error = exception.message();
    }

    return version;
}

bool BSPFormatReader::read(const QJsonDocument &document, BSPFileStructure& outFile, QString &error)
{
    bool success = false;

    m_pCurrentFile = &outFile;
    m_pCurrentFile->clear();

    try
    {
        readJsonDocument(document);
        success = true;
    }
    catch (GenericException& exception)
    {
        error = exception.message();
    }

    m_pCurrentFile = nullptr;
    return success;
}

quint32 BSPFormatReader::readVersionInternal(const QJsonDocument& document)
{
    quint32 version = JSONReaderItem::getRootObjectItem(document)
            ->getObjectItemOfType<quint32>("version");

    if ( version == 0 )
    {
        throw GenericException("Version identifier cannot be zero.");
    }

    return version;
}

void BSPFormatReader::readJsonDocument(const QJsonDocument& document)
{
    m_pCurrentFile->setVersion(readVersionInternal(document));
    readLumpList(JSONReaderItem::getRootObjectItem(document));
}

void BSPFormatReader::readLumpList(const JSONReaderItemPtr& root)
{
    JSONReaderItemPtr lumpsList = root->getObjectItem("lumps", QJsonValue::Array);
    JSONReaderItemPtr lumpItemsObject = root->getObjectItem("lumpitems", QJsonValue::Object);
    int lumpCount = (*lumpsList)->toArray().count();

    for ( int lumpIndex = 0; lumpIndex < lumpCount; ++lumpIndex )
    {
        QSharedPointer<BSPLumpDef> lumpDef(new BSPLumpDef());

        lumpDef->setName(lumpsList->getArrayItemOfType<QString>(lumpIndex));
        m_pCurrentFile->addLumpDef(lumpDef);

        readLumpData(lumpDef, lumpItemsObject);
    }
}

void BSPFormatReader::readLumpData(const QSharedPointer<BSPLumpDef> &lumpDef,
                                   const JSONReaderItemPtr &lumpItemsObject)
{
    JSONReaderItemPtr lumpItem = lumpItemsObject->getObjectItem(lumpDef->name(), QJsonValue::Object);
    QString lumpItemType = lumpItem->getObjectItemOfType<QString>("type");

    try
    {
        BSPLumpDef::LumpType type = BSPLumpDef::lumpTypeNameMap().value(lumpItemType);
        lumpDef->setType(type);
    }
    catch (QException&)
    {
        throw GenericException(QString("Lump type '%0' unrecognised.").arg(lumpItemType));
    }
}
