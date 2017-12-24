#include "bspfile.h"
#include <QFile>

BSPFile::BSPFile(QObject *parent)
    : QObject(parent),
      m_strFilePath(),
      m_arrData()
{
}

QString BSPFile::filePath() const
{
    return m_strFilePath;
}

const QByteArray& BSPFile::contents() const
{
    return m_arrData;
}

bool BSPFile::isValid() const
{
    return !m_strFilePath.isEmpty();
}

bool BSPFile::load(const QString &filePath)
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
    emit loaded();
    return true;
}

void BSPFile::clear()
{
    bool wasValid = isValid();

    m_strFilePath.clear();
    m_arrData.clear();

    if ( wasValid )
    {
        emit cleared();
    }
}
