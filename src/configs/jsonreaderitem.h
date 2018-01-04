#ifndef JSONREADPATHTRACKERITEM_H
#define JSONREADPATHTRACKERITEM_H

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QSharedPointer>

#include "jsonreaderutil.h"
#include "jsonreaderexception.h"

class JSONReaderItem;
typedef QSharedPointer<JSONReaderItem> JSONReaderItemPtr;

class JSONReaderItem
{
public:
    ~JSONReaderItem();

    bool isValid() const;

    QJsonValue* operator ->();
    QJsonValue& operator *();

    void validate(QJsonValue::Type type) const;

    static JSONReaderItemPtr getRootObjectItem(const QJsonDocument& document);
    static JSONReaderItemPtr getRootArrayItem(const QJsonDocument& document);

    JSONReaderItemPtr getObjectItem(const QString& key, QJsonValue::Type desiredType = QJsonValue::Undefined);
    JSONReaderItemPtr getArrayItem(int index, QJsonValue::Type desiredType = QJsonValue::Undefined);

    QString computePath() const;

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

    inline JSONReaderException createException(const QString& message)
    {
        return JSONReaderException(computePath(), message);
    }

private:
    JSONReaderItem(const JSONReaderItemPtr& parentItem,
                            const QString& parentKey,
                            QJsonValue parentValue);

    template<typename T>
    JSONReaderItemPtr getItemForType(const T& key, QJsonValue::Type desiredType);
    void setWeakSelf(const QWeakPointer<JSONReaderItem>& weakSelf);

    // A reference to the parent item is kept. This is to
    // help ensure that destruction order occurs correctly,
    // as the parent will not die while its children are alive.
    // This means the object needs to know about its own shared
    // pointer family, but it shouldn't keep a shared pointer
    // to itself or it will never die. Therefore it keeps a
    // weak pointer, which is promoted when creating children.
    QWeakPointer<JSONReaderItem> m_pWeakSelf;

    // This is the actual shared pointer to the parent.
    JSONReaderItemPtr m_pParentItem;

    QString m_strParentKey;
    QJsonValue m_ParentValue;
};

#endif // JSONREADPATHTRACKERITEM_H
