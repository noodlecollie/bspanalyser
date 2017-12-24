#ifndef BSPFILESTRUCTURE_H
#define BSPFILESTRUCTURE_H

#include <QVector>
#include <QSharedPointer>

#include "bsplumpdef.h"

class BSPFileStructure
{
public:
    BSPFileStructure();

    quint32 version() const;
    void setVersion(quint32 newVersion);

    void addLumpDef(const QSharedPointer<BSPLumpDef>& lump);
    int lumpDefCount() const;
    void clearLumpDefs();
    QSharedPointer<BSPLumpDef> lumpDef(int index) const;

private:
    quint32 m_nVersion;
    QVector<QSharedPointer<BSPLumpDef>> m_liLumpDefs;
};

#endif // BSPFILESTRUCTURE_H
