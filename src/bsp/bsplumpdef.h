#ifndef BSPLUMPDEF_H
#define BSPLUMPDEF_H

#include <QString>
#include <QObject>

#include "ibspdataitem.h"
#include "util/enumnamemap.h"

class BSPLumpDef : public IBSPDataItem
{
    Q_GADGET
public:
    // Different possible types for lumps.
    enum class LumpType
    {
        Keyvalues,          // Holds ASCII keyvalues data for entities.
        Struct,             // Holds some number data items of a given structure.
        VisData,            // Holds visibility data.
        EmbeddedTextures    // Contains texture files.
    };
    Q_ENUM(LumpType)

    static QSharedPointer<BSPLumpDef> createEmptyLumpDef(const QString& name, LumpType type);

    BSPLumpDef();
    static const EnumNameMap<LumpType>& lumpTypeNameMap();

    // Returns the entire lump data from the file.
    virtual BSPDataFragment getDataFragment(const BSPFileModel &data) const override;

    QString name() const;
    void setName(const QString& newName);

    quint32 index() const;
    void setIndex(quint32 newIndex);

    LumpType type() const;
    void setType(LumpType newType);

    bool isValid() const;

private:
    quint32 headerLumpByteOffset(const BSPFileModel &data) const;

    QString m_strName;
    quint32 m_nIndex;
    BSPLumpDef::LumpType m_nType;
};

#endif // BSPLUMPDEF_H
