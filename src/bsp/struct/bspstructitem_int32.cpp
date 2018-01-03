#include "bspstructitem_int32.h"

BSPStructItem_Int32::BSPStructItem_Int32(BSPStruct *parent, bool isUnsigned)
    : BSPStructItem_Integer(parent, isUnsigned ? BSPStructItem::ItemType::UInt32 : BSPStructItem::ItemType::Int32)
{

}

quint32 BSPStructItem_Int32::size() const
{
    return sizeof(qint32);
}
