#ifndef STRUCTLUMPDEF_H
#define STRUCTLUMPDEF_H

#include "bsplumpdef.h"

#include "struct/bspstruct.h"

class StructLumpDef : public BSPLumpDef
{
public:
    StructLumpDef();

    BSPStruct& bspStruct();
    const BSPStruct& bspStruct() const;
    QByteArray getDataForIndex(const QByteArray& lumpData, quint32 index) const;

private:
    BSPStruct m_Struct;
};

#endif // STRUCTLUMPDEF_H
