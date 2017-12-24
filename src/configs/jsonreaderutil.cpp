#include "jsonreaderutil.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QtGlobal>

#include "readerexception.h"

namespace JSONReaderUtil
{
    QString TypeNameString(QJsonValue::Type type)
    {
        switch (type)
        {
            case QJsonValue::Null:
            {
                return "Null";
            }

            case QJsonValue::Bool:
            {
                return "Bool";
            }

            case QJsonValue::Double:
            {
                return "Double";
            }

            case QJsonValue::String:
            {
                return "String";
            }

            case QJsonValue::Array:
            {
                return "Array";
            }

            case QJsonValue::Object:
            {
                return "Object";
            }

            default:
            {
                return "Undefined";
            }
        }
    }

    void ValidateType(const QJsonValue& value, QJsonValue::Type expectedType)
    {
        if ( value.type() != expectedType )
        {
            throw ReaderException(QString("Expected JSON value of type '%0' but got '%1'.")
                                  .arg(TypeNameString(expectedType))
                                  .arg(TypeNameString(value.type())));
        }
    }

    template<typename T>
    T ValueToType(const QJsonValue& value)
    {
        // Specalised below.
        return T();
    }

    template<>
    QJsonArray ValueToType(const QJsonValue& value)
    {
        return value.toArray();
    }

    template<>
    bool ValueToType(const QJsonValue& value)
    {
        return value.toBool();
    }

    template<>
    double ValueToType(const QJsonValue& value)
    {
        return value.toDouble();
    }

    template<>
    qint32 ValueToType(const QJsonValue& value)
    {
        return value.toInt();
    }

    template<>
    quint32 ValueToType(const QJsonValue& value)
    {
        return static_cast<quint32>(value.toInt());
    }

    template<>
    QJsonObject ValueToType(const QJsonValue& value)
    {
        return value.toObject();
    }

    template<>
    QString ValueToType(const QJsonValue& value)
    {
        return value.toString();
    }

    template<>
    QVariant ValueToType(const QJsonValue& value)
    {
        return value.toVariant();
    }

    template<typename T>
    QJsonValue::Type EnumValueForType()
    {
        // Specialised below.
        return QJsonValue::Undefined;
    }

    template<>
    QJsonValue::Type EnumValueForType<QJsonArray>()
    {
        return QJsonValue::Array;
    }

    template<>
    QJsonValue::Type EnumValueForType<bool>()
    {
        return QJsonValue::Bool;
    }

    template<>
    QJsonValue::Type EnumValueForType<double>()
    {
        return QJsonValue::Double;
    }

    template<>
    QJsonValue::Type EnumValueForType<qint32>()
    {
        return EnumValueForType<double>();
    }

    template<>
    QJsonValue::Type EnumValueForType<quint32>()
    {
        return EnumValueForType<double>();
    }

    template<>
    QJsonValue::Type EnumValueForType<QJsonObject>()
    {
        return QJsonValue::Object;
    }

    template<>
    QJsonValue::Type EnumValueForType<QString>()
    {
        return QJsonValue::String;
    }
}
