#include "bspstructitem_int16.h"

BSPStructItem_Int16::BSPStructItem_Int16(BSPStruct *parent, bool isUnsigned)
    : BSPStructItem_Integer(parent, isUnsigned ? BSPStructItem::ItemType::UInt16 : BSPStructItem::ItemType::Int16)
{

}

quint32 BSPStructItem_Int16::size() const
{
    return sizeof(qint16);
}
