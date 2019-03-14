#include "bsplumpdef.h"

#include "bspdefs.h"
#include "structlumpdef.h"
#include "visibilitylumpdef.h"
#include "model/bspfilemodel.h"

namespace
{
    struct HeaderLump
    {
        quint32 offset;
        quint32 length;
    };
}

BSPLumpDef::BSPLumpDef()
    : m_strName(),
      m_nIndex(0),
      m_nType(LumpType::Struct)
{

}

QSharedPointer<BSPLumpDef> BSPLumpDef::createEmptyLumpDef(const QString& name, LumpType type)
{
    QSharedPointer<BSPLumpDef> lumpDef;

    switch (type)
    {
        case LumpType::Struct:
        {
            lumpDef = QSharedPointer<BSPLumpDef>(new StructLumpDef());
            break;
        }

        case LumpType::VisData:
        {
            lumpDef = QSharedPointer<BSPLumpDef>(new VisibilityLumpDef());
            break;
        }

        case LumpType::Keyvalues:
        case LumpType::EmbeddedTextures:
        {
            lumpDef = QSharedPointer<BSPLumpDef>(new BSPLumpDef());
            break;
        }

        default:
        {
            throw EnumValueNotFoundException();
        }
    }

    lumpDef->setName(name);
    lumpDef->setType(type);

    return lumpDef;
}

const EnumNameMap<BSPLumpDef::LumpType>& BSPLumpDef::lumpTypeNameMap()
{
    static const EnumNameMap<BSPLumpDef::LumpType> typeNameMap(BSPLumpDef::staticMetaObject, "LumpType");
    return typeNameMap;
}

BSPDataFragment BSPLumpDef::getDataFragment(const BSPFileModel &data) const
{
    const QByteArray& contents = data.contents();

    if ( !isValid() )
    {
        return BSPDataFragment(contents);
    }

    quint32 length = static_cast<quint32>(contents.length());
    quint64 offset = headerLumpByteOffset(data);

    if ( length < offset + BSPDefs::HEADER_LUMP_DEF_BYTES )
    {
        return BSPDataFragment(contents);
    }

    const HeaderLump* headerLump = reinterpret_cast<const HeaderLump*>(contents.constData() + offset);

    // The lump info from the BSP header then tells us the offset and length of the actual data.
    if ( length < headerLump->offset + headerLump->length )
    {
        return BSPDataFragment(contents);
    }

    return BSPDataFragment(contents, headerLump->offset, headerLump->length);
}

bool BSPLumpDef::isValid() const
{
    return !m_strName.isNull();
}

QString BSPLumpDef::name() const
{
    return m_strName;
}

void BSPLumpDef::setName(const QString &newName)
{
    if ( newName.isNull() )
    {
        return;
    }

    m_strName = newName;
}

quint32 BSPLumpDef::index() const
{
    return m_nIndex;
}

void BSPLumpDef::setIndex(quint32 newIndex)
{
    m_nIndex = newIndex;
}

quint64 BSPLumpDef::headerLumpByteOffset(const BSPFileModel &data) const
{
    return data.lumpTableOffset() + (m_nIndex * BSPDefs::HEADER_LUMP_DEF_BYTES);
}

BSPLumpDef::LumpType BSPLumpDef::type() const
{
    return m_nType;
}

void BSPLumpDef::setType(LumpType newType)
{
    m_nType = newType;
}
