#ifndef BSPSTRUCTITEM_INT16_H
#define BSPSTRUCTITEM_INT16_H

#include "bspstructitem_integer.h"

class BSPStructItem_Int16 : public BSPStructItem_Integer
{
    Q_OBJECT
public:
    BSPStructItem_Int16(BSPStruct* parent, bool isUnsigned);

    virtual quint32 size() const override;
};

#endif // BSPSTRUCTITEM_INT16_H
