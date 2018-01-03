#include "bspstructitem_integer.h"

BSPStructItem_Integer::BSPStructItem_Integer(BSPStruct *parent, BSPStructItem::ItemType type)
    : BSPStructItem(parent, type)
{

}

bool BSPStructItem_Integer::isUnsigned() const
{
    return typeIsUnsigned(type());
}
