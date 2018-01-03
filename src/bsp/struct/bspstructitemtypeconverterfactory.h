#ifndef BSPSTRUCTITEMTYPECONVERTERFACTORY_H
#define BSPSTRUCTITEMTYPECONVERTERFACTORY_H

#include <QSharedPointer>

#include "bspstructgenericblock.h"
#include "bspstructitemtypeconverter.h"

namespace BSPStructItemTypeConverterFactory
{
    QSharedPointer<BSPStructItemTypeConverter> createConverter(const BSPStructGenericBlock& member);
}

#endif // BSPSTRUCTITEMTYPECONVERTERFACTORY_H
