#include "bspstructitem.h"

#include "bspstruct.h"

BSPStructItem::BSPStructItem(BSPStruct *parent, ItemType type)
    : QObject(parent),
      m_nType(type),
      m_nOffsetInParent(0)
{
    Q_ASSERT_X(typeIsValid(m_nType), Q_FUNC_INFO, "Struct item must be valid!");
}

BSPStructItem::IndexType BSPStructItem::indexTypeOfItem(ItemType type)
{
    // Assumes only one index flag is present on the type.
    switch ( static_cast<ItemType>(static_cast<quint32>(type) & ~static_cast<quint32>(ItemType::Mask_LegalType)) )
    {
        case ItemType::Mod_IsPrimaryIndex:
        {
            return IndexType::PrimaryIndex;
        }

        case ItemType::Mod_IsPrimaryOffset:
        {
            return IndexType::PrimaryOffset;
        }

        case ItemType::Mod_IsSecondaryIndex:
        {
            return IndexType::SecondaryIndex;
        }

        case ItemType::Mod_IsBinaryIndex:
        {
            return IndexType::BinaryIndex;
        }

        default:
        {
            return IndexType::NoIndex;
        }
    }
}

const EnumNameMap<BSPStructItem::ItemType>& BSPStructItem::itemTypeNameMap()
{
    static EnumNameMap<BSPStructItem::ItemType> nameMap(BSPStructItem::staticMetaObject, "ItemType");
    return nameMap;
}

BSPStruct* BSPStructItem::parentStruct() const
{
    return qobject_cast<BSPStruct*>(parent());
}

quint32 BSPStructItem::offsetInParent() const
{
    return m_nOffsetInParent;
}

BSPStructItem::ItemType BSPStructItem::type() const
{
    return m_nType;
}

void BSPStructItem::setOffsetInParent(quint32 offset)
{
    m_nOffsetInParent = offset;
}
