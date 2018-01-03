#include "structlumpdef.h"

StructLumpDef::StructLumpDef()
    : BSPLumpDef(),
      m_Struct()
{

}

BSPStruct& StructLumpDef::bspStruct()
{
    return m_Struct;
}
