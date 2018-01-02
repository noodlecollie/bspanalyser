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
        m_pCurrentFile->clear();
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

    readAllLumps(lumpsList, lumpItemsObject);
    linkLumps(lumpItemsObject);
}

void BSPFormatReader::readAllLumps(const JSONReaderItemPtr& lumpsList, const JSONReaderItemPtr& lumpItemsObject)
{
    int lumpCount = (*lumpsList)->toArray().count();

    for ( int lumpIndex = 0; lumpIndex < lumpCount; ++lumpIndex )
    {
        QString lumpName = lumpsList->getArrayItemOfType<QString>(lumpIndex);
        QSharedPointer<BSPLumpDef> lumpDef = readLumpData(lumpName, lumpItemsObject);
        Q_ASSERT(lumpDef);

        m_pCurrentFile->addLumpDef(lumpDef);
    }
}

QSharedPointer<BSPLumpDef> BSPFormatReader::readLumpData(const QString& lumpName, const JSONReaderItemPtr& lumpItemsObject)
{
    JSONReaderItemPtr lumpItem = lumpItemsObject->getObjectItem(lumpName, QJsonValue::Object);
    QString lumpItemType = lumpItem->getObjectItemOfType<QString>("type");
    QSharedPointer<BSPLumpDef> lumpDef;

    try
    {
        lumpDef = BSPLumpDef::createEmptyLumpDef(lumpName, BSPLumpDef::lumpTypeNameMap().value(lumpItemType));
        if ( !lumpDef )
        {
            // Just throw some exception.
            // Doesn't really matter what, as long as it's caught below.
            throw GenericException("Unrecognised");
        }
    }
    catch (EnumValueNotFoundException&)
    {
        throw GenericException(QString("Lump type '%0' unrecognised.").arg(lumpItemType));
    }

    switch (lumpDef->type())
    {
        case BSPLumpDef::LumpType::VisData:
        {
            readLumpData(lumpDef.staticCast<VisibilityLumpDef>(), lumpItem);
            break;
        }

        case BSPLumpDef::LumpType::Struct:
        {
            readLumpData(lumpDef.staticCast<StructLumpDef>(), lumpItem);
            break;
        }

        default:
        {
            break;
        }
    }

    return lumpDef;
}

void BSPFormatReader::readLumpData(const QSharedPointer<VisibilityLumpDef>& lump, const JSONReaderItemPtr& lumpJson)
{
    lump->setIsCompressed(lumpJson->getObjectItemOfType<bool>("rle"));
}

void BSPFormatReader::readLumpData(const QSharedPointer<StructLumpDef>& lump, const JSONReaderItemPtr& lumpJson)
{
    // TODO
    Q_UNUSED(lump);
    Q_UNUSED(lumpJson);
}

void BSPFormatReader::linkLumps(const JSONReaderItemPtr& lumpItemsObject)
{
    for ( int lumpIndex = 0; lumpIndex < m_pCurrentFile->lumpDefCount(); ++lumpIndex )
    {
        QSharedPointer<BSPLumpDef> lumpDef = m_pCurrentFile->lumpDef(lumpIndex);
        JSONReaderItemPtr lumpItem = lumpItemsObject->getObjectItem(lumpDef->name(), QJsonValue::Object);

        switch ( lumpDef->type() )
        {
            case BSPLumpDef::LumpType::VisData:
            {
                linkLump(lumpDef.staticCast<VisibilityLumpDef>(), lumpItem);
                break;
            }

            case BSPLumpDef::LumpType::Struct:
            {
                linkLump(lumpDef.staticCast<StructLumpDef>(), lumpItem);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void BSPFormatReader::linkLump(const QSharedPointer<VisibilityLumpDef> &lump, const JSONReaderItemPtr &lumpJson)
{
    QString leavesLumpName = lumpJson->getObjectItemOfType<QString>("leaveslump");
    QSharedPointer<BSPLumpDef> leavesLumpDef = m_pCurrentFile->lumpDef(leavesLumpName);

    if ( !leavesLumpDef )
    {
        throw GenericException(QString("Visibility lump '%0' references leaves lump '%1' which was not found.")
                               .arg(lump->name())
                               .arg(leavesLumpName));
    }

    if ( leavesLumpDef->type() != BSPLumpDef::LumpType::Struct )
    {
        throw GenericException(QString("Visibility lump '%0' references leaves lump '%1' "
                                       "which was of type '%2', not '%3'.")
                               .arg(lump->name())
                               .arg(leavesLumpName)
                               .arg(BSPLumpDef::lumpTypeNameMap().key(leavesLumpDef->type()))
                               .arg(BSPLumpDef::lumpTypeNameMap().key(BSPLumpDef::LumpType::Struct)));
    }

    lump->setLeavesLump(leavesLumpDef.staticCast<StructLumpDef>());
}

void BSPFormatReader::linkLump(const QSharedPointer<StructLumpDef> &lump, const JSONReaderItemPtr &lumpJson)
{
    // TODO
    Q_UNUSED(lump);
    Q_UNUSED(lumpJson);
}
