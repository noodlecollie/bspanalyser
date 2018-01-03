#include "bspstructitem_integer.h"

BSPStructItem_Integer::BSPStructItem_Integer(BSPStruct *parent, BSPStructItem::ItemType type)
    : BSPStructItem(parent, type)
{

}

bool BSPStructItem_Integer::isUnsigned() const
{
    return typeIsUnsigned(type());
}

BSPStructItem::IndexType BSPStructItem_Integer::indexType() const
{
    return indexTypeOfItem(type());
}

quint32 BSPStructItem_Integer::size() const
{
    switch ( BSPStructItem::unmodifiedType(type()) )
    {
        case ItemType::Int8:
        {
            return sizeof(qint8);
        }

        case ItemType::Int16:
        {
            return sizeof(qint16);
        }

        case ItemType::Int32:
        {
            return sizeof(qint32);
        }

        default:
        {
            return 0;
        }
    }
}
