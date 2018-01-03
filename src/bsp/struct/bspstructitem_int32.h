#ifndef BSPSTRUCTITEM_INT32_H
#define BSPSTRUCTITEM_INT32_H

#include "bspstructitem_integer.h"

class BSPStructItem_Int32 : public BSPStructItem_Integer
{
    Q_OBJECT
public:
    BSPStructItem_Int32(BSPStruct* parent, bool isUnsigned);

    virtual quint32 size() const override;
};

#endif // BSPSTRUCTITEM_INT32_H
