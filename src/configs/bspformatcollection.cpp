#include "bspformatcollection.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>

#include "bspformatreader.h"

Q_LOGGING_CATEGORY(lcBSPFormatCollection, "BSPFormatCollection")

BSPFormatCollection::BSPFormatCollection()
    : m_hshFormatFiles(),
      m_hshFormatFileNames(),
      m_hshVersionHasSubVersions()
{

}

void BSPFormatCollection::initialise()
{
    QDir formatDir(":/formats");
    QStringList formatFiles = formatDir.entryList(QStringList() << "*.json");

    for ( const QString& file : formatFiles )
    {
        loadFormat(formatDir.filePath(file));
    }
}

bool BSPFormatCollection::hasFormat(quint32 version) const
{
    return m_hshFormatFiles.contains(version);
}

QSharedPointer<QByteArray> BSPFormatCollection::format(const QByteArray& data) const
{
    const quint32* versionPtr = reinterpret_cast<const quint32*>(data.constData());
    quint64 version = static_cast<quint64>(versionPtr[0]);

    if ( m_hshVersionHasSubVersions.contains(version) )
    {
        // Include sub-version.
        version |= static_cast<quint64>(versionPtr[1]) << 32;
    }

    return m_hshFormatFiles.value(version, QSharedPointer<QByteArray>());
}

void BSPFormatCollection::loadFormat(const QString &filePath)
{
    QFile file(filePath);
    if ( !file.open(QIODevice::ReadOnly) )
    {
        qCWarning(lcBSPFormatCollection) << "Unable to open format file" << filePath;
        return;
    }

    QByteArray contents = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(contents, &parseError);

    if ( parseError.error != QJsonParseError::NoError )
    {
        qCWarning(lcBSPFormatCollection).nospace() << "Error reading format JSON from " << filePath
                                                   << ". At character " << parseError.offset << ": " << parseError.errorString();
        return;
    }

    BSPFormatReader formatReader;
    QString errorString;
    quint32 version = formatReader.readVersion(jsonDoc, errorString);

    if ( version == 0 )
    {
        qCWarning(lcBSPFormatCollection).nospace() << "Error interpreting format JSON from " << filePath << ". " << errorString;
        return;
    }

    // First check for formats which don't have sub-versions.
    // The unadorned version number can just be used as a key.
    if ( m_hshFormatFiles.contains(version) && !m_hshVersionHasSubVersions.value(version) )
    {
        qCWarning(lcBSPFormatCollection).nospace() << "Error reading format JSON from " << filePath
                                                   << ". A format document for version " << version << " already exists at "
                                                   << m_hshFormatFileNames.value(version) << ".";
        return;
    }

    quint32 subVersion = 0;
    bool hasSubVersion = formatReader.readSubVersion(jsonDoc, subVersion, errorString);

    // Sub-versions get or'd in with the version.
    quint64 versionKey = (static_cast<quint64>(subVersion) << 32) | static_cast<quint64>(version);

    if ( m_hshFormatFiles.contains(versionKey) )
    {
        qCWarning(lcBSPFormatCollection).nospace() << "Error reading format JSON from " << filePath
                                                   << ". A format document for version " << version << ", sub-version "
                                                   << subVersion << " already exists at " << m_hshFormatFileNames.value(versionKey) << ".";
        return;
    }

    QSharedPointer<QByteArray> jsonBinaryData(new QByteArray());
    m_hshFormatFiles.insert(versionKey, jsonBinaryData);
    m_hshFormatFileNames.insert(versionKey, filePath);

    if ( hasSubVersion )
    {
        m_hshVersionHasSubVersions.insert(version, true);
    }
    else if ( !m_hshVersionHasSubVersions.contains(version) )
    {
        m_hshVersionHasSubVersions.insert(version, false);
    }

    int length = 0;
    const char* rawData = jsonDoc.rawData(&length);
    jsonBinaryData->resize(length);
    memcpy(jsonBinaryData->data(), rawData, length);

    qCDebug(lcBSPFormatCollection).nospace() << "Loaded "
                                             << (filePath.startsWith(":") ? "built-in" : "custom")
                                             << " format " << filePath << " for BSP version "
                                             << version << (hasSubVersion ? QString(", sub-version %0").arg(subVersion).toLatin1().constData() : "") << ".";
}

QString BSPFormatCollection::sourceFileName(quint32 version) const
{
    return m_hshFormatFileNames.value(version);
}
