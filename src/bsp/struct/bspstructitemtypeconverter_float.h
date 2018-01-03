#ifndef BSPSTRUCTITEMTYPECONVERTER_FLOAT_H
#define BSPSTRUCTITEMTYPECONVERTER_FLOAT_H

#include "bspstructitemtypeconverter.h"

class BSPStructItemTypeConverter_Float : public BSPStructItemTypeConverter
{
public:
    BSPStructItemTypeConverter_Float(const BSPStructGenericBlock& member);

    virtual QString toString(const QByteArray &structData, quint32 index) override;
};

#endif // BSPSTRUCTITEMTYPECONVERTER_FLOAT_H
