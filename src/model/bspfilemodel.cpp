#include "bspfilemodel.h"
#include <QFile>

#include "exceptions/genericexception.h"
#include "bsp/bspdefs.h"

BSPFileModel::BSPFileModel(QObject *parent)
    : QObject(parent),
      m_strFilePath(),
      m_arrData(),
      m_bHasSubVersion(false)
{
}

QString BSPFileModel::filePath() const
{
    return m_strFilePath;
}

const QByteArray& BSPFileModel::contents() const
{
    return m_arrData;
}

quint32 BSPFileModel::version() const
{
    if ( static_cast<quint64>(m_arrData.length()) < sizeof(quint32) )
    {
        throw GenericException("Not enough data in BSP file to provide version.");
    }

    return *reinterpret_cast<const quint32*>(m_arrData.constData());
}

quint32 BSPFileModel::subVersion() const
{
    if ( !m_bHasSubVersion )
    {
        throw GenericException("BSP file does not have a sub-version.");
    }

    if ( static_cast<quint64>(m_arrData.length()) < 2 * sizeof(quint32) )
    {
        throw GenericException("Not enough data in BSP file to provide sub-version.");
    }

    return *(reinterpret_cast<const quint32*>(m_arrData.constData()) + 1);
}

quint64 BSPFileModel::lumpTableOffset() const
{
    return BSPDefs::VERSION_BYTES +
           (m_bHasSubVersion ? BSPDefs::SUBVERSION_BYTES : 0);
}

bool BSPFileModel::hasSubVersion() const
{
    return m_bHasSubVersion;
}

void BSPFileModel::setHasSubVersion(bool hasSV)
{
    m_bHasSubVersion = hasSV;
}

bool BSPFileModel::isValid() const
{
    return !m_strFilePath.isEmpty();
}

bool BSPFileModel::load(const QString &filePath)
{
    if ( filePath.isEmpty() )
    {
        return false;
    }

    QFile file(filePath);
    if ( !file.open(QIODevice::ReadOnly) )
    {
        return false;
    }

    m_arrData = file.readAll();
    m_strFilePath = filePath;

    file.close();
    return true;
}

void BSPFileModel::clear()
{
    m_strFilePath.clear();
    m_arrData.clear();
}
