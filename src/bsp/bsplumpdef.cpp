#include "bsplumpdef.h"

#include "bspdefs.h"
#include "structlumpdef.h"
#include "visibilitylumpdef.h"

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
        case LumpType::Keyvalues:
        {
            lumpDef = QSharedPointer<BSPLumpDef>(new BSPLumpDef());
            break;
        }

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

        default:
        {
            break;
        }
    }

    if ( lumpDef )
    {
        lumpDef->setName(name);
        lumpDef->setType(type);
    }

    return lumpDef;
}

const EnumNameMap<BSPLumpDef::LumpType>& BSPLumpDef::lumpTypeNameMap()
{
    static const EnumNameMap<BSPLumpDef::LumpType> typeNameMap(BSPLumpDef::staticMetaObject, "LumpType");
    return typeNameMap;
}

BSPDataFragment BSPLumpDef::getDataFragment(const QByteArray &data) const
{
    if ( !isValid() )
    {
        return BSPDataFragment(data);
    }

    quint32 dataLength = data.length();
    quint32 offset = headerLumpByteOffset();

    if ( dataLength < offset + BSPDefs::HEADER_LUMP_DEF_BYTES )
    {
        return BSPDataFragment(data);
    }

    const HeaderLump* headerLump = reinterpret_cast<const HeaderLump*>(data.constData() + offset);

    // The lump info from the BSP header then tells us the offset and length of the actual data.
    if ( dataLength < headerLump->offset + headerLump->length )
    {
        return BSPDataFragment(data);
    }

    return BSPDataFragment(data, headerLump->offset, headerLump->length);
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

quint32 BSPLumpDef::headerLumpByteOffset() const
{
    return BSPDefs::VERSION_BYTES + (m_nIndex * BSPDefs::HEADER_LUMP_DEF_BYTES);
}

BSPLumpDef::LumpType BSPLumpDef::type() const
{
    return m_nType;
}

void BSPLumpDef::setType(LumpType newType)
{
    m_nType = newType;
}
