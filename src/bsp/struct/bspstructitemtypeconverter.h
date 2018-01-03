#ifndef BSPSTRUCTITEMTYPECONVERTER_H
#define BSPSTRUCTITEMTYPECONVERTER_H

#include <QVariant>
#include <QByteArray>

class BSPStructGenericBlock;

class BSPStructItemTypeConverter
{
public:
    virtual ~BSPStructItemTypeConverter();
    virtual QVariant value(const QByteArray& structData, quint32 index = 0) = 0;

protected:
    BSPStructItemTypeConverter(const BSPStructGenericBlock& member);

    const BSPStructGenericBlock& m_Member;
};

#endif // BSPSTRUCTITEMTYPECONVERTER_H
