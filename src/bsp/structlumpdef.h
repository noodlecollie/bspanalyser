#ifndef STRUCTLUMPDEF_H
#define STRUCTLUMPDEF_H

#include "bsplumpdef.h"

#include "struct/bspstruct.h"

class StructLumpDef : public BSPLumpDef
{
public:
    StructLumpDef();

    BSPStruct& bspStruct();
    QByteArray getDataForItem(const QByteArray& lumpData, quint32 item) const;

private:
    BSPStruct m_Struct;
};

#endif // STRUCTLUMPDEF_H
