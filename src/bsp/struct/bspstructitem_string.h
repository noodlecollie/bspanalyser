#ifndef BSPSTRUCTITEM_STRING_H
#define BSPSTRUCTITEM_STRING_H

#include "bspstructitem.h"

class BSPStructItem_String : public BSPStructItem
{
public:
    BSPStructItem_String(BSPStruct* parent, quint32 maxLength);

    virtual quint32 size() const override;

private:
    quint32 m_nMaxLength;
};

#endif // BSPSTRUCTITEM_STRING_H
