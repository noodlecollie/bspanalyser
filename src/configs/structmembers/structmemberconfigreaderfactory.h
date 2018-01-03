#ifndef STRUCTMEMBERCONFIGREADERFACTORY_H
#define STRUCTMEMBERCONFIGREADERFACTORY_H

#include <QSharedPointer>

#include "configs/structmembers/structmemberconfigreader.h"
#include "bsp/struct/bspstructitemtypes.h"

namespace StructMemberConfigReaderFactory
{
    QSharedPointer<StructMemberConfigReader> createReader(BSPStructItemTypes::CoreItemType type,
                                                          const QSharedPointer<StructLumpDef>& structLumpDef,
                                                          const JSONReaderItemPtr& memberObject,
                                                          quint32 count = 1);
}

#endif // STRUCTMEMBERCONFIGREADERFACTORY_H
