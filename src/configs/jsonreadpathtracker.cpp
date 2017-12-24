#include "jsonreadpathtracker.h"

JSONReadPathTracker::JSONReadPathTracker()
    : m_pDocument(nullptr),
      m_stackPath()
{
}

JSONReadPathTracker::JSONReadPathTracker(const QJsonDocument &document)
    : m_pDocument(&document),
      m_stackPath()
{

}

QString JSONReadPathTracker::currentPath() const
{
    QString buildPath = "";

    for ( QStack<QString>::const_iterator pathSeg = m_stackPath.constBegin(); pathSeg != m_stackPath.constEnd(); ++pathSeg )
    {
        if ( !buildPath.isEmpty() )
        {
            buildPath += ".";
        }

        buildPath += *pathSeg;
    }

    return buildPath;
}

QString JSONReadPathTracker::cachedPath() const
{
    return m_strCachedPath;
}

void JSONReadPathTracker::cacheCurrentPath()
{
    m_strCachedPath = currentPath();
}

const QJsonDocument* JSONReadPathTracker::document() const
{
    return m_pDocument;
}

void JSONReadPathTracker::pushPathSegment(const QString &segment)
{
    m_stackPath.push(segment);
}

void JSONReadPathTracker::popPathSegment()
{
    if ( m_stackPath.isEmpty() )
    {
        return;
    }

    m_stackPath.pop();
}

QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTracker::getRootObjectItem()
{
    QSharedPointer<JSONReadPathTrackerItem> item(
                new JSONReadPathTrackerItem(this, QSharedPointer<JSONReadPathTrackerItem>(), "root", m_pDocument && m_pDocument->isObject() ? QJsonValue(m_pDocument->object()) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());
    item->validate(QJsonValue::Object);
    return item;
}

QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTracker::getRootArrayItem()
{
    QSharedPointer<JSONReadPathTrackerItem> item(
                new JSONReadPathTrackerItem(this, QSharedPointer<JSONReadPathTrackerItem>(), "root", m_pDocument && m_pDocument->isArray() ? QJsonValue(m_pDocument->array()) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());
    item->validate(QJsonValue::Array);
    return item;
}
