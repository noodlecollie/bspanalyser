#ifndef BSPSTRUCTITEMTYPECONVERTER_INTEGER_H
#define BSPSTRUCTITEMTYPECONVERTER_INTEGER_H

#include "bspstructitemtypeconverter.h"

class BSPStructItemTypeConverter_Integer : public BSPStructItemTypeConverter
{
public:
    BSPStructItemTypeConverter_Integer(const BSPStructGenericBlock& member);

    virtual QVariant value(const QByteArray& structData, quint32 index) override;

private:
    union SignedUnsignedInt32
    {
        qint32 signedVal;
        quint32 unsignedVal;
    };
};

#endif // BSPSTRUCTITEMTYPECONVERTER_INTEGER_H
