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

bool BSPFormatReader::readSubVersion(const QJsonDocument& document, quint32& subVersion, QString& error)
{
    try
    {
        subVersion = readSubVersionInternal(document);
        return true;
    }
    catch (GenericException& exception)
    {
        error = exception.message();
        return false;
    }
}

bool BSPFormatReader::read(const QJsonDocument &document, BSPFileStructure& outFile, QString &error)
{
    bool success = false;

    m_pCurrentFile = &outFile;
    m_pCurrentFile->clear();
    m_liLumpReaders.clear();

    try
    {
        readJsonDocument(document);
        success = true;
    }
    catch (GenericException& exception)
    {
        error = exception.message();
        m_pCurrentFile->clear();
    }

    m_liLumpReaders.clear();
    m_pCurrentFile = nullptr;
    return success;
}

quint32 BSPFormatReader::readVersionInternal(const QJsonDocument& document)
{
    quint32 version = JSONReaderItem::getRootObjectItem(document)->getObjectItemOfType<quint32>("version");

    if ( version == 0 )
    {
        throw GenericException("Version identifier cannot be zero.");
    }

    return version;
}

quint32 BSPFormatReader::readSubVersionInternal(const QJsonDocument& document)
{
    return JSONReaderItem::getRootObjectItem(document)->getObjectItemOfType<quint32>("subVersion");
}

void BSPFormatReader::readJsonDocument(const QJsonDocument& document)
{
    m_pCurrentFile->setVersion(readVersionInternal(document));

    try
    {
        m_pCurrentFile->setSubVersion(readSubVersionInternal(document));
    }
    catch (GenericException&)
    {
        m_pCurrentFile->setHasSubVersion(false);
    }

    readLumpList(JSONReaderItem::getRootObjectItem(document));
}

void BSPFormatReader::readLumpList(const JSONReaderItemPtr& root)
{
    JSONReaderItemPtr lumpsList = root->getObjectItem("lumps", QJsonValue::Array);
    JSONReaderItemPtr lumpItemsObject = root->getObjectItem("lumpitems", QJsonValue::Object);

    readAllLumps(lumpsList, lumpItemsObject);
    linkLumps();
}

void BSPFormatReader::readAllLumps(const JSONReaderItemPtr& lumpsList, const JSONReaderItemPtr& lumpItemsObject)
{
    int lumpCount = (*lumpsList)->toArray().count();

    for ( int lumpIndex = 0; lumpIndex < lumpCount; ++lumpIndex )
    {
        QString lumpName = lumpsList->getArrayItemOfType<QString>(lumpIndex);
        JSONReaderItemPtr lumpItem = lumpItemsObject->getObjectItem(lumpName, QJsonValue::Object);
        QString lumpTypeString = lumpItem->getObjectItemOfType<QString>("type");
        QSharedPointer<AbstractLumpConfigReader> lumpReader;

        try
        {
            BSPLumpDef::LumpType lumpType = BSPLumpDef::lumpTypeNameMap().value(lumpTypeString);
            lumpReader = AbstractLumpConfigReader::createReader(lumpName, lumpType);
        }
        catch (EnumValueNotFoundException&)
        {
            throw JSONReaderException(lumpItem->getObjectItem("type")->computePath(),
                                      QString("Lump '%0' had unrecognised type '%1'.")
                                      .arg(lumpName)
                                      .arg(lumpTypeString));
        }

        lumpReader->setLumpItemsObject(lumpItemsObject);
        lumpReader->setBspFileStructure(m_pCurrentFile);
        lumpReader->readLumpData();

        QSharedPointer<BSPLumpDef> lumpDefPointer = lumpReader->lumpDef();
        Q_ASSERT(lumpDefPointer);

        m_pCurrentFile->addLumpDef(lumpDefPointer);
        m_liLumpReaders.append(lumpReader);
    }
}

void BSPFormatReader::linkLumps()
{
    for ( const QSharedPointer<AbstractLumpConfigReader>& lumpReader : m_liLumpReaders )
    {
        lumpReader->link();
    }
}
