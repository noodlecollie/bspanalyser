#ifndef BSPSTRUCTITEMTYPECONVERTER_H
#define BSPSTRUCTITEMTYPECONVERTER_H

#include <QString>
#include <QByteArray>

#include "bspstructgenericblock.h"

class BSPStructItemTypeConverter
{
public:
    virtual QString toString(const QByteArray& structData, quint32 index = 0) = 0;

protected:
    BSPStructItemTypeConverter(const BSPStructGenericBlock& member);

    const BSPStructGenericBlock& m_Member;
};

#endif // BSPSTRUCTITEMTYPECONVERTER_H
