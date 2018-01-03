#include "bspstructitem_string.h"

BSPStructItem_String::BSPStructItem_String(BSPStruct *parent, quint32 maxLength)
    : BSPStructItem(parent, ItemType::String),
      m_nMaxLength(maxLength)
{

}

quint32 BSPStructItem_String::size() const
{
    return m_nMaxLength;
}
