#ifndef BSPSTRUCT_H
#define BSPSTRUCT_H

#include <QObject>
#include <QVector>

#include "bspstructitemtypes.h"
#include "bspstructgenericblock.h"

class BSPStruct
{
public:
    BSPStruct();
    ~BSPStruct();

    BSPStructGenericBlock* addMember(BSPStructItemTypes::CoreItemType type, quint32 count = 1);
    void clear();

private:
    QVector<BSPStructGenericBlock*> m_liMembers;
};

#endif // BSPSTRUCT_H
