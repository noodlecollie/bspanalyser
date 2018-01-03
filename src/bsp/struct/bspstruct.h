#ifndef BSPSTRUCT_H
#define BSPSTRUCT_H

#include <QObject>
#include <QVector>

#include "bspstructitemtypes.h"
#include "bspstructgenericblock.h"

class BSPStruct : public QObject
{
    Q_OBJECT
public:
    BSPStruct(QObject* parent = nullptr);
    ~BSPStruct();

    bool addMember(BSPStructItemTypes::CoreItemType type, quint32 count = 1);

private:
    QVector<BSPStructGenericBlock*> m_liMembers;
};

#endif // BSPSTRUCT_H
