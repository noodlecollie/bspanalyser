#ifndef BSPSTRUCTITEMATTRIBUTES_H
#define BSPSTRUCTITEMATTRIBUTES_H

#include <QHash>
#include <QVariant>
#include <QObject>

#include "util/enumnamemap.h"

class BSPStructItemAttributes
{
    Q_GADGET
public:
    BSPStructItemAttributes();

    enum class Attribute
    {
        Enum,           // Name of enum to check values against.
        DisplayHex,     // Display numerical values as hex.
    };
    Q_ENUM(Attribute)

    QVariant attributeValue(Attribute att) const;
    void setAttributeValue(Attribute att, const QVariant& value);
    void clearAttribute(Attribute att);

    static const EnumNameMap<Attribute>& attributeNameMap();

private:
    QHash<Attribute, QVariant> m_hshAttributes;
};

uint qHash(BSPStructItemAttributes::Attribute key, uint seed);

#endif // BSPSTRUCTITEMATTRIBUTES_H
