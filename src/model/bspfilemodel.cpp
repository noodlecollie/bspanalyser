#include "bspfilemodel.h"
#include <QFile>

BSPFileModel::BSPFileModel(QObject *parent)
    : QObject(parent),
      m_strFilePath(),
      m_arrData()
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
