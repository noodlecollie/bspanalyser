#ifndef BSPSTRUCTITEMTYPECONVERTER_FVECTOR_H
#define BSPSTRUCTITEMTYPECONVERTER_FVECTOR_H

#include "bspstructitemtypeconverter.h"

class BSPStructItemTypeConverter_FVector : public BSPStructItemTypeConverter
{
public:
    BSPStructItemTypeConverter_FVector(const BSPStructGenericBlock& member);

    virtual QString toString(const QByteArray &structData, quint32 index) override;

private:
    template<quint32 COUNT>
    struct LocalFVector
    {
        float components[COUNT];
    };
};

#endif // BSPSTRUCTITEMTYPECONVERTER_FVECTOR_H
