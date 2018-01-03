#ifndef BSPSTRUCT_H
#define BSPSTRUCT_H

#include <QObject>
#include <QVector>

#include "bspstructitem.h"
class BSPStruct : public QObject
{
    Q_OBJECT
public:
    BSPStruct(QObject* parent = nullptr);

    void appendItem(BSPStructItem::ItemType type,
                    quint32 arrayCount = 1,
                    BSPStructItem::ItemType arrayType = BSPStructItem::ItemType::Invalid);

private:
    BSPStructItem* createItem(BSPStructItem::ItemType type, quint32 count);

    QVector<BSPStructItem*> m_liMembers;
};

#endif // BSPSTRUCT_H
