#ifndef JSONREADERUTIL_H
#define JSONREADERUTIL_H

#include <QJsonValue>
#include <QString>

namespace JSONReaderUtil
{
    QString TypeNameString(QJsonValue::Type type);

    // Specialised for supported types.
    template<typename T>
    T ValueToType(const QJsonValue& value);

    // Specialised for supported types.
    // Returns QJsonValue::Undefined otherwise.
    template<typename T>
    QJsonValue::Type EnumValueForType();
}

#endif // JSONREADERUTIL_H
