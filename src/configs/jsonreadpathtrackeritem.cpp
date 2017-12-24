#include "jsonreadpathtrackeritem.h"

#include "jsonreadpathtracker.h"

JSONReadPathTrackerItem::JSONReadPathTrackerItem(JSONReadPathTracker* parent,
                                                 const QSharedPointer<JSONReadPathTrackerItem>& parentItem,
                                                 const QString& parentKey,
                                                 QJsonValue parentValue)
    : m_pParent(parent),
      m_pWeakSelf(),
      m_pParentItem(parentItem),
      m_strParentKey(parentKey),
      m_ParentValue(parentValue)
{
    m_pParent->pushPathSegment(parentKey);
    m_pParent->cacheCurrentPath();
}

JSONReadPathTrackerItem::~JSONReadPathTrackerItem()
{
    m_pParent->popPathSegment();
}

void JSONReadPathTrackerItem::setWeakSelf(const QWeakPointer<JSONReadPathTrackerItem> &weakSelf)
{
    m_pWeakSelf = weakSelf;
}

bool JSONReadPathTrackerItem::isValid() const
{
    return !m_ParentValue.isUndefined();
}

QJsonValue* JSONReadPathTrackerItem::operator ->()
{
    return &m_ParentValue;
}

QJsonValue& JSONReadPathTrackerItem::operator *()
{
    return m_ParentValue;
}

void JSONReadPathTrackerItem::validate(QJsonValue::Type type)
{
    JSONReaderUtil::ValidateType(m_ParentValue, type);
}

QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTrackerItem::getObjectItem(const QString& key, QJsonValue::Type desiredType)
{
    QSharedPointer<JSONReadPathTrackerItem> item(
                new JSONReadPathTrackerItem(m_pParent, m_pWeakSelf.toStrongRef(), key, m_ParentValue.isObject() ? m_ParentValue.toObject().value(key) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());

    if ( desiredType != QJsonValue::Undefined )
    {
        item->validate(desiredType);
    }

    return item;
}

QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTrackerItem::getArrayItem(int index, QJsonValue::Type desiredType)
{
    QSharedPointer<JSONReadPathTrackerItem> item(
                new JSONReadPathTrackerItem(m_pParent, m_pWeakSelf.toStrongRef(), QString("[%0]").arg(index), m_ParentValue.isArray() ? m_ParentValue.toArray()[index] : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());

    if ( desiredType != QJsonValue::Undefined )
    {
        item->validate(desiredType);
    }

    return item;
}

template<typename T>
QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTrackerItem::getItemForType(const T& key, QJsonValue::Type desiredType)
{
    // Specialised below.
    return QSharedPointer<JSONReadPathTrackerItem>();
}

template<>
QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTrackerItem::getItemForType(const QString& key, QJsonValue::Type desiredType)
{
    return getObjectItem(key, desiredType);
}

template<>
QSharedPointer<JSONReadPathTrackerItem> JSONReadPathTrackerItem::getItemForType(const int& index, QJsonValue::Type desiredType)
{
    return getArrayItem(index, desiredType);
}
