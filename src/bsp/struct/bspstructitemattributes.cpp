#include "bspstructitemattributes.h"

uint qHash(BSPStructItemAttributes::Attribute key, uint seed)
{
    return qHash(static_cast<quint32>(key), seed);
}

BSPStructItemAttributes::BSPStructItemAttributes()
    : m_hshAttributes()
{

}

const EnumNameMap<BSPStructItemAttributes::Attribute>& BSPStructItemAttributes::attributeNameMap()
{
    static EnumNameMap<BSPStructItemAttributes::Attribute> nameMap(BSPStructItemAttributes::staticMetaObject, "Attribute");
    return nameMap;
}

QVariant BSPStructItemAttributes::attributeValue(Attribute att) const
{
    return m_hshAttributes.value(att, QVariant());
}

void BSPStructItemAttributes::setAttributeValue(Attribute att, const QVariant &value)
{
    m_hshAttributes.insert(att, value);
}

void BSPStructItemAttributes::clearAttribute(Attribute att)
{
    m_hshAttributes.remove(att);
}
