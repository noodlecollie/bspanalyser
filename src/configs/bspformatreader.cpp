#include "bspformatreader.h"

#include "exceptions/genericexception.h"
#include "jsonreaderutil.h"

BSPFormatReader::BSPFormatReader()
    : m_pCurrentFile(nullptr),
      m_JsonTracker()
{

}

quint32 BSPFormatReader::readVersion(const QJsonDocument& document, QString& error)
{
    quint32 version = 0;
    m_JsonTracker = JSONReadPathTracker(document);

    try
    {
        version = readVersionInternal(m_JsonTracker);
    }
    catch (GenericException& exception)
    {
        error = QString("Error reading version ('%0'). %1").arg(m_JsonTracker.cachedPath()).arg(exception.message());
    }

    m_JsonTracker = JSONReadPathTracker();
    return version;
}

bool BSPFormatReader::read(const QJsonDocument &document, BSPFileStructure& outFile, QString &error)
{
    bool success = false;

    m_pCurrentFile = &outFile;
    m_JsonTracker = JSONReadPathTracker(document);

    try
    {
        readJsonDocument(m_JsonTracker);
        success = true;
    }
    catch (GenericException& exception)
    {
        error = QString("Error encountered at '%0'. %1").arg(m_JsonTracker.cachedPath()).arg(exception.message());
    }

    m_pCurrentFile = nullptr;
    m_JsonTracker = JSONReadPathTracker();
    return success;
}

quint32 BSPFormatReader::readVersionInternal(JSONReadPathTracker &json)
{
    quint32 version = json.getRootObjectItem()->getObjectItemOfType<quint32>("version");

    if ( version == 0 )
    {
        throw GenericException("Version identifier cannot be zero.");
    }

    return version;
}

void BSPFormatReader::readJsonDocument(JSONReadPathTracker& json)
{
    m_pCurrentFile->setVersion(readVersionInternal(json));
    readLumpList(json.getRootObjectItem());
}

void BSPFormatReader::readLumpList(const QSharedPointer<JSONReadPathTrackerItem>& root)
{
    QSharedPointer<JSONReadPathTrackerItem> lumpsList = root->getObjectItem("lumps", QJsonValue::Array);
    int lumpCount = (*lumpsList)->toArray().count();

    for ( int lumpIndex = 0; lumpIndex < lumpCount; ++lumpIndex )
    {
        QSharedPointer<BSPLumpDef> lumpDef(new BSPLumpDef());

        lumpDef->setName(lumpsList->getArrayItemOfType<QString>(lumpIndex));
        m_pCurrentFile->addLumpDef(lumpDef);
    }
}
