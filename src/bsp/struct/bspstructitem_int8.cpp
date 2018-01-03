#include "bspstructitem_int8.h"

BSPStructItem_Int8::BSPStructItem_Int8(BSPStruct *parent, bool isUnsigned)
    : BSPStructItem_Integer(parent, isUnsigned ? BSPStructItem::ItemType::UInt8 : BSPStructItem::ItemType::Int8)
{

}

quint32 BSPStructItem_Int8::size() const
{
    return sizeof(qint8);
}
