#ifndef BSPSTRUCTITEM_FLOAT_H
#define BSPSTRUCTITEM_FLOAT_H

#include "bspstructitem.h"

class BSPStructItem_Float : public BSPStructItem
{
    Q_OBJECT
public:
    BSPStructItem_Float(BSPStruct* parent);

    virtual quint32 size() const override;
};

#endif // BSPSTRUCTITEM_FLOAT_H
