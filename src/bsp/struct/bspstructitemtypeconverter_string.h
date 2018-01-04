#ifndef BSPSTRUCTITEMTYPECONVERTER_STRING_H
#define BSPSTRUCTITEMTYPECONVERTER_STRING_H

#include "bspstructitemtypeconverter.h"

class BSPStructItemTypeConverter_String : public BSPStructItemTypeConverter
{
public:
    BSPStructItemTypeConverter_String(const BSPStructGenericBlock& member);
    virtual ~BSPStructItemTypeConverter_String();

    virtual QVariant value(const QByteArray& structData, quint32 index) override;
};

#endif // BSPSTRUCTITEMTYPECONVERTER_STRING_H
