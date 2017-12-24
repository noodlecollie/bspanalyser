#ifndef JSONREADPATHTRACKERITEM_H
#define JSONREADPATHTRACKERITEM_H

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QSharedPointer>

#include "jsonreaderutil.h"

class JSONReadPathTracker;

class JSONReadPathTrackerItem
{
    friend class JSONReadPathTracker;

    JSONReadPathTrackerItem(JSONReadPathTracker* parent,
                            const QSharedPointer<JSONReadPathTrackerItem>& parentItem,
                            const QString& parentKey,
                            QJsonValue parentValue);
    void setWeakSelf(const QWeakPointer<JSONReadPathTrackerItem>& weakSelf);

public:
    ~JSONReadPathTrackerItem();

    bool isValid() const;

    QJsonValue* operator ->();
    QJsonValue& operator *();

    void validate(QJsonValue::Type type);

    QSharedPointer<JSONReadPathTrackerItem> getObjectItem(const QString& key, QJsonValue::Type desiredType = QJsonValue::Undefined);
    QSharedPointer<JSONReadPathTrackerItem> getArrayItem(int index, QJsonValue::Type desiredType = QJsonValue::Undefined);

    template<typename T>
    T getObjectItemOfType(const QString& key)
    {
        return JSONReaderUtil::ValueToType<T>(**getItemForType<QString>(key, JSONReaderUtil::EnumValueForType<T>()));
    }

    template<typename T>
    T getArrayItemOfType(int index)
    {
        return JSONReaderUtil::ValueToType<T>(**getItemForType<int>(index, JSONReaderUtil::EnumValueForType<T>()));
    }

private:
    template<typename T>
    QSharedPointer<JSONReadPathTrackerItem> getItemForType(const T& key, QJsonValue::Type desiredType);

    JSONReadPathTracker* m_pParent;

    // A reference to the parent item is kept. This is to
    // help ensure that destruction order occurs correctly,
    // as the parent will not die while its children are alive.
    // This means the object needs to know about its own shared
    // pointer family, but it shouldn't keep a shared pointer
    // to itself or it will never die. Therefore it keeps a
    // weak pointer, which is promoted when creating children.
    QWeakPointer<JSONReadPathTrackerItem> m_pWeakSelf;

    // This is the actual shared pointer to the parent.
    QSharedPointer<JSONReadPathTrackerItem> m_pParentItem;

    QString m_strParentKey;
    QJsonValue m_ParentValue;
};

#endif // JSONREADPATHTRACKERITEM_H
