#ifndef BSPSTRUCTITEM_INTEGER_H
#define BSPSTRUCTITEM_INTEGER_H

#include "bspstructitem.h"

class BSPStructItem_Integer : public BSPStructItem
{
    Q_OBJECT
public:
    BSPStructItem_Integer(BSPStruct* parent, BSPStructItem::ItemType type);

    bool isUnsigned() const;
    IndexType indexType() const;

    virtual quint32 size() const override;
};

#endif // BSPSTRUCTITEM_INTEGER_H
