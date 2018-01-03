#include "bspstruct.h"

#include "bspstructitem_int8.h"
#include "bspstructitem_int16.h"
#include "bspstructitem_int32.h"

#include "exceptions/genericexception.h"

BSPStructItem* BSPStruct::createItem(BSPStructItem::ItemType type)
{
    if ( !BSPStructItem::typeIsValidForConstruction(type) )
    {
        throw GenericException(QString("Struct item type '%0' was not valid.")
                               .arg(BSPStructItem::itemTypeNameMap().key(type)));
    }

    switch (type)
    {
        case BSPStructItem::ItemType::Int8:
        case BSPStructItem::ItemType::UInt8:
        {
            return new BSPStructItem_Int8(this, BSPStructItem::typeIsUnsigned(type));
        }

        case BSPStructItem::ItemType::Int16:
        case BSPStructItem::ItemType::UInt16:
        {
            return new BSPStructItem_Int16(this, BSPStructItem::typeIsUnsigned(type));
        }

        case BSPStructItem::ItemType::Int32:
        case BSPStructItem::ItemType::UInt32:
        {
            return new BSPStructItem_Int32(this, BSPStructItem::typeIsUnsigned(type));
        }

        default:
        {
            return nullptr;
        }
    }
}

BSPStruct::BSPStruct(QObject *parent)
    : QObject(parent)
{

}

void BSPStruct::appendItem(BSPStructItem::ItemType type,
                           quint32 arrayCount,
                           BSPStructItem::ItemType arrayType)
{
    // TODO: Implement arrays.
    Q_UNUSED(arrayCount);
    Q_UNUSED(arrayType);

    BSPStructItem* item = createItem(type);
    Q_ASSERT(item);

    quint32 nextOffset = 0;
    if ( !m_liMembers.isEmpty() )
    {
        BSPStructItem* lastItem = m_liMembers.last();
        nextOffset = lastItem->offsetInParent() + lastItem->size();
    }

    item->setOffsetInParent(nextOffset);
    m_liMembers.append(item);
}
