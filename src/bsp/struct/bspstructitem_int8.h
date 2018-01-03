#ifndef BSPSTRUCTITEM_UINT8_H
#define BSPSTRUCTITEM_UINT8_H

#include "bspstructitem_integer.h"

class BSPStructItem_Int8 : public BSPStructItem_Integer
{
    Q_OBJECT
public:
    BSPStructItem_Int8(BSPStruct* parent, bool isUnsigned);

    virtual quint32 size() const override;
};

#endif // BSPSTRUCTITEM_UINT8_H
