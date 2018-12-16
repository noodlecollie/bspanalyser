#ifndef BSPFILESTRUCTURE_H
#define BSPFILESTRUCTURE_H

#include <QVector>
#include <QSharedPointer>

#include "bsplumpdef.h"

class BSPFileStructure
{
public:
    BSPFileStructure();

    void clear();

    quint32 version() const;
    void setVersion(quint32 newVersion);

    quint32 subVersion() const;
    void setSubVersion(quint32 newSubVersion);

    bool hasSubVersion() const;
    void setHasSubVersion(bool hasSV);

    void addLumpDef(const QSharedPointer<BSPLumpDef>& lump);
    int lumpDefCount() const;
    void clearLumpDefs();
    QSharedPointer<BSPLumpDef> lumpDef(int index) const;
    QSharedPointer<BSPLumpDef> lumpDef(const QString& name) const;

private:
    quint32 m_nVersion;
    quint32 m_nSubVersion;
    bool m_bHasSubVersion;
    QVector<QSharedPointer<BSPLumpDef>> m_liLumpDefs;
};

#endif // BSPFILESTRUCTURE_H
