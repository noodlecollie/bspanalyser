#ifndef ABSTRACTLUMPCONFIGREADER_H
#define ABSTRACTLUMPCONFIGREADER_H

#include <QSharedPointer>
#include <QString>

#include "jsonreaderitem.h"

#include "bsp/bsplumpdef.h"
#include "bsp/bspfilestructure.h"

class AbstractLumpConfigReader
{
public:
    AbstractLumpConfigReader();
    virtual ~AbstractLumpConfigReader();

    static QSharedPointer<AbstractLumpConfigReader> createReader(const QString& lumpName, BSPLumpDef::LumpType type);

    void setLumpItemsObject(const JSONReaderItemPtr& object);
    void setBspFileStructure(BSPFileStructure* file);
    bool isValid() const;

    void readLumpData();
    void link();
    QSharedPointer<BSPLumpDef> lumpDef() const;

protected:
    AbstractLumpConfigReader(const QString& lumpName);

    virtual QSharedPointer<BSPLumpDef> createLumpDef() = 0;
    virtual void readLumpDataInternal() = 0;
    virtual void linkInternal() = 0;

    QString m_strLumpName;
    JSONReaderItemPtr m_pLumpItemsObject;
    BSPFileStructure* m_pBspFileStructure;
    QSharedPointer<BSPLumpDef> m_pLumpDef;
};

#endif // ABSTRACTLUMPCONFIGREADER_H
