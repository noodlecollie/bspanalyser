#include "jsonreaderitem.h"

#include <QJsonDocument>

JSONReaderItem::JSONReaderItem(const JSONReaderItemPtr& parentItem,
                                                 const QString& parentKey,
                                                 QJsonValue parentValue)
    : m_pWeakSelf(),
      m_pParentItem(parentItem),
      m_strParentKey(parentKey),
      m_ParentValue(parentValue)
{
}

JSONReaderItem::~JSONReaderItem()
{
}

void JSONReaderItem::setWeakSelf(const QWeakPointer<JSONReaderItem> &weakSelf)
{
    m_pWeakSelf = weakSelf;
}

bool JSONReaderItem::isValid() const
{
    return !m_ParentValue.isUndefined();
}

QJsonValue* JSONReaderItem::operator ->()
{
    return &m_ParentValue;
}

QJsonValue& JSONReaderItem::operator *()
{
    return m_ParentValue;
}

void JSONReaderItem::validate(QJsonValue::Type type) const
{
    if ( m_ParentValue.type() != type )
    {
        throw JSONReaderException(computePath(),
                                  QString("Expected JSON value of type '%0' but got '%1'.")
                                      .arg(JSONReaderUtil::TypeNameString(type))
                                      .arg(JSONReaderUtil::TypeNameString(m_ParentValue.type())));
    }
}

JSONReaderItemPtr JSONReaderItem::getRootObjectItem(const QJsonDocument &document)
{
    JSONReaderItemPtr item(
                new JSONReaderItem(JSONReaderItemPtr(),
                                            "root",
                                            document.isObject() ? QJsonValue(document.object()) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());
    item->validate(QJsonValue::Object);

    return item;
}

JSONReaderItemPtr JSONReaderItem::getRootArrayItem(const QJsonDocument &document)
{
    JSONReaderItemPtr item(
                new JSONReaderItem(JSONReaderItemPtr(),
                                            "root",
                                            document.isArray() ? QJsonValue(document.array()) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());
    item->validate(QJsonValue::Array);

    return item;
}

JSONReaderItemPtr JSONReaderItem::getObjectItem(const QString& key, QJsonValue::Type desiredType)
{
    JSONReaderItemPtr item(
                new JSONReaderItem(m_pWeakSelf.toStrongRef(),
                                            key,
                                            m_ParentValue.isObject() ? m_ParentValue.toObject().value(key) : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());

    if ( desiredType != QJsonValue::Undefined )
    {
        item->validate(desiredType);
    }

    return item;
}

JSONReaderItemPtr JSONReaderItem::getArrayItem(int index, QJsonValue::Type desiredType)
{
    JSONReaderItemPtr item(
                new JSONReaderItem(m_pWeakSelf.toStrongRef(),
                                            QString("[%0]").arg(index),
                                            m_ParentValue.isArray() ? m_ParentValue.toArray()[index] : QJsonValue()));

    item->setWeakSelf(item.toWeakRef());

    if ( desiredType != QJsonValue::Undefined )
    {
        item->validate(desiredType);
    }

    return item;
}

template<typename T>
JSONReaderItemPtr JSONReaderItem::getItemForType(const T&, QJsonValue::Type)
{
    // Specialised below.
    return JSONReaderItemPtr();
}

template<>
JSONReaderItemPtr JSONReaderItem::getItemForType(const QString& key, QJsonValue::Type desiredType)
{
    return getObjectItem(key, desiredType);
}

template<>
JSONReaderItemPtr JSONReaderItem::getItemForType(const int& index, QJsonValue::Type desiredType)
{
    return getArrayItem(index, desiredType);
}

QString JSONReaderItem::computePath() const
{
    QString path = m_strParentKey;

    for ( JSONReaderItemPtr parent = m_pParentItem; parent; parent = parent->m_pParentItem )
    {
        if ( !parent->m_strParentKey.isEmpty() )
        {
            path = parent->m_strParentKey + "." + path;
        }
    }

    return path;
}
