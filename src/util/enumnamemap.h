#ifndef ENUMNAMEMAP_H
#define ENUMNAMEMAP_H

#include <QString>
#include <QMetaObject>
#include <QMetaEnum>
#include <QHash>

#include "exceptions/enumvaluenotfoundexception.h"

template<typename ENUM>
class EnumNameMap
{
public:
    EnumNameMap(const QMetaObject& metaObject, const char* enumName);

    ENUM value(const QString& key) const;
    inline ENUM operator [](const QString& key) const
    {
        return value(key);
    }

    QString key(ENUM value) const;

private:
    QMetaEnum m_TargetEnum;
    QHash<QString, ENUM> m_hshLowercaseNameMap;
};

template<typename ENUM>
EnumNameMap<ENUM>::EnumNameMap(const QMetaObject& metaObject, const char* enumName)
    : m_TargetEnum(metaObject.enumerator(metaObject.indexOfEnumerator(enumName)))
{
    Q_ASSERT_X(m_TargetEnum.isValid(), Q_FUNC_INFO, "Specified enum was not valid.");

    int keyCount = m_TargetEnum.keyCount();

    for ( int keyIndex = 0; keyIndex < keyCount; ++keyIndex )
    {
        const char* key = m_TargetEnum.key(keyIndex);
        ENUM value = static_cast<ENUM>(m_TargetEnum.keyToValue(key));

        m_hshLowercaseNameMap.insert(QString(key).toLower(), value);
    }
}

template<typename ENUM>
ENUM EnumNameMap<ENUM>::value(const QString &key) const
{
    QString lowercaseKey = key.toLower();
    if ( !m_hshLowercaseNameMap.contains(lowercaseKey) )
    {
        throw EnumValueNotFoundException();
    }

    return m_hshLowercaseNameMap.value(lowercaseKey);
}

template<typename ENUM>
QString EnumNameMap<ENUM>::key(ENUM value) const
{
    return m_TargetEnum.valueToKey(static_cast<int>(value));
}

#endif // ENUMNAMEMAP_H
