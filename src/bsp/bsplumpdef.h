#ifndef BSPLUMPDEF_H
#define BSPLUMPDEF_H

#include <QString>

#include "ibspdataitem.h"

class BSPLumpDef : public IBSPDataItem
{
public:
    BSPLumpDef();

    // Returns the entire lump data from the file.
    virtual BSPDataFragment getDataFragment(const QByteArray &data) const override;

    QString name() const;
    void setName(const QString& newName);

    quint32 index() const;
    void setIndex(quint32 newIndex);

    bool isValid() const;

private:
    quint32 headerLumpByteOffset() const;

    QString m_strName;
    quint32 m_nIndex;
};

#endif // BSPLUMPDEF_H
