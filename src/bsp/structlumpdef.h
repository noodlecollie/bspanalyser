#ifndef STRUCTLUMPDEF_H
#define STRUCTLUMPDEF_H

#include "bsplumpdef.h"

#include "struct/bspstruct.h"

class StructLumpDef : public BSPLumpDef
{
public:
    StructLumpDef();

    BSPStruct& bspStruct();

private:
    BSPStruct m_Struct;
};

#endif // STRUCTLUMPDEF_H
