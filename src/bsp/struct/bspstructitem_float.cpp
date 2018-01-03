#include "bspstructitem_float.h"

BSPStructItem_Float::BSPStructItem_Float(BSPStruct *parent)
    : BSPStructItem(parent, ItemType::Float)
{
}

quint32 BSPStructItem_Float::size() const
{
    return sizeof(float);
}
