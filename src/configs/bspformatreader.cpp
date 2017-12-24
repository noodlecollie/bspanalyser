#include "bspformatreader.h"

#include "readerexception.h"
#include "jsonreaderutil.h"

BSPFormatReader::BSPFormatReader()
    : m_pCurrentFile(nullptr),
      m_JsonTracker()
{

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
    catch (ReaderException& exception)
    {
        error = QString("Error encountered at '%0'. %1").arg(m_JsonTracker.cachedPath()).arg(exception.message());
    }

    m_pCurrentFile = nullptr;
    return success;
}

void BSPFormatReader::readJsonDocument(JSONReadPathTracker& json)
{
    QSharedPointer<JSONReadPathTrackerItem> rootObject = json.getRootObjectItem();
    m_pCurrentFile->setVersion(rootObject->getObjectItemOfType<quint32>("version"));
}
