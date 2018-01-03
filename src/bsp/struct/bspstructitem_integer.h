#ifndef BSPSTRUCTITEM_INTEGER_H
#define BSPSTRUCTITEM_INTEGER_H

#include "bspstructitem.h"

class BSPStructItem_Integer : public BSPStructItem
{
    Q_OBJECT
protected:
    BSPStructItem_Integer(BSPStruct* parent, BSPStructItem::ItemType type);

    bool isUnsigned() const;
};

#endif // BSPSTRUCTITEM_INTEGER_H
