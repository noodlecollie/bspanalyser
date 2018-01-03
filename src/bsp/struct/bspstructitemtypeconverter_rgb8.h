#ifndef BSPSTRUCTITEMTYPECONVERTER_RGB8_H
#define BSPSTRUCTITEMTYPECONVERTER_RGB8_H

#include "bspstructitemtypeconverter.h"

class BSPStructItemTypeConverter_RGB8 : public BSPStructItemTypeConverter
{
public:
    BSPStructItemTypeConverter_RGB8(const BSPStructGenericBlock& member);
    ~BSPStructItemTypeConverter_RGB8();

    virtual QVariant value(const QByteArray &structData, quint32 index) override;

private:
    struct LocalRGB8
    {
        quint8 colour[3];
    };
};

#endif // BSPSTRUCTITEMTYPECONVERTER_RGB8_H
