#include "bspformatcollection.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>

#include "bspformatreader.h"

Q_LOGGING_CATEGORY(lcBSPFormatCollection, "BSPFormatCollection")

BSPFormatCollection::BSPFormatCollection()
    : m_hshFormatFiles(),
      m_hshFormatFileNames()
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

QSharedPointer<QByteArray> BSPFormatCollection::format(quint32 version) const
{
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
        qCWarning(lcBSPFormatCollection).nospace() << "Error reading format JSON from " << filePath << ". " << parseError.errorString();
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

    QSharedPointer<QByteArray> jsonBinaryData(new QByteArray());
    m_hshFormatFiles.insert(version, jsonBinaryData);
    m_hshFormatFileNames.insert(version, filePath);

    int length = 0;
    const char* rawData = jsonDoc.rawData(&length);
    jsonBinaryData->resize(length);
    memcpy(jsonBinaryData->data(), rawData, length);

    qCDebug(lcBSPFormatCollection) << "Loaded format" << filePath;
}

QString BSPFormatCollection::sourceFileName(quint32 version) const
{
    return m_hshFormatFileNames.value(version);
}
