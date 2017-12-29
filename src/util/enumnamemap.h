#ifndef ENUMNAMEMAP_H
#define ENUMNAMEMAP_H

#include <QString>
#include <QMetaObject>
#include <QMetaEnum>
#include <QException>
#include <QHash>

template<typename ENUM>
class EnumNameMap
{
public:
    class ValueNotFoundException : public QException
    {
    public:
        virtual void raise() const override
        {
            throw *this;
        }
        virtual QException *clone() const override
        {
            return new ValueNotFoundException(*this);
        }
    };

    EnumNameMap(const QMetaObject& metaObject, const char* enumName);

    ENUM value(const QString& key) const;
    inline ENUM operator [](const QString& key) const
    {
        return value(key);
    }

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
        throw ValueNotFoundException();
    }

    return m_hshLowercaseNameMap.value(lowercaseKey);
}

#endif // ENUMNAMEMAP_H
