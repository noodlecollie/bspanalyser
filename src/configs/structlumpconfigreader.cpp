#include "structlumpconfigreader.h"

#include "exceptions/enumvaluenotfoundexception.h"
#include "configs/structmembers/structmemberconfigreaderfactory.h"

StructLumpConfigReader::StructLumpConfigReader(const QString &lumpName)
    : AbstractLumpConfigReader(lumpName)
{
}

StructLumpConfigReader::~StructLumpConfigReader()
{
}

QSharedPointer<BSPLumpDef> StructLumpConfigReader::createLumpDef()
{
    QSharedPointer<BSPLumpDef> lump = BSPLumpDef::createEmptyLumpDef(m_strLumpName, BSPLumpDef::LumpType::Struct);
    m_pStructLumpDef = lump.staticCast<StructLumpDef>();
    return lump;
}

void StructLumpConfigReader::readLumpDataInternal()
{
    JSONReaderItemPtr lumpItem = getLumpItemObject();
    JSONReaderItemPtr membersArray = lumpItem->getObjectItem("members", QJsonValue::Array);
    int membersCount = (*membersArray)->toArray().count();

    for ( int memberIndex = 0; memberIndex < membersCount; ++memberIndex )
    {
        readMember(membersArray->getArrayItem(memberIndex, QJsonValue::Object));
    }
}

void StructLumpConfigReader::readMember(const JSONReaderItemPtr &memberObject)
{
    QString memberName = memberObject->getObjectItemOfType<QString>("name");

    BSPStructItemTypes::PublicItemType memberType = getPublicType(memberObject, "type");
    m_nCurrentCoreType = static_cast<BSPStructItemTypes::CoreItemType>(memberType);
    m_nCurrentItemCount = 1;

    checkForArrayType(memberObject);

    QSharedPointer<StructMemberConfigReader> memberReader =
            StructMemberConfigReaderFactory::createReader(m_nCurrentCoreType,
                                                          m_pStructLumpDef,
                                                          memberObject,
                                                          static_cast<quint32>(m_nCurrentItemCount));

    BSPStructGenericBlock* member = memberReader->loadAndCreateMember();
    Q_ASSERT(member);

    member->setName(memberName);
}

void StructLumpConfigReader::checkForArrayType(const JSONReaderItemPtr &memberObject)
{
    if ( BSPStructItemTypes::unmodifiedCoreType(m_nCurrentCoreType) == BSPStructItemTypes::Meta_Array )
    {
        if ( BSPStructItemTypes::coreTypeHasModifier(m_nCurrentCoreType, BSPStructItemTypes::Mod_InterpretAsString) )
        {
            m_nCurrentCoreType = BSPStructItemTypes::Type_StringChar;
            m_nCurrentItemCount = memberObject->getObjectItemOfType<qint32>("stringsize");

            if ( m_nCurrentItemCount < 1 )
            {
                throw memberObject->getObjectItem("stringsize")->createException("String size must be greater than 0.");
            }
        }
        else
        {
            BSPStructItemTypes::PublicItemType arrayType = getPublicType(memberObject, "arraytype");
            m_nCurrentCoreType = static_cast<BSPStructItemTypes::CoreItemType>(arrayType);

            if ( BSPStructItemTypes::unmodifiedCoreType(m_nCurrentCoreType) == BSPStructItemTypes::Meta_Array )
            {
                throw memberObject->getObjectItem("arraytype")->createException("Array type must be a primitive.");
            }

            m_nCurrentItemCount = memberObject->getObjectItemOfType<qint32>("arraycount");
            if ( m_nCurrentItemCount < 1 )
            {
                throw memberObject->getObjectItem("arraycount")->createException("Array count must be greater than 0.");
            }
        }
    }
}

BSPStructItemTypes::PublicItemType StructLumpConfigReader::getPublicType(const JSONReaderItemPtr& memberObject, const QString& key)
{
    QString typeString = memberObject->getObjectItemOfType<QString>(key);

    try
    {
        return BSPStructItemTypes::publicItemTypeNameMap().value(typeString);
    }
    catch (EnumValueNotFoundException&)
    {
        throw memberObject->getObjectItem(key)->createException(QString("Value of '%0' was unrecognised.")
                                                                .arg(typeString));
    }
}

void StructLumpConfigReader::linkInternal()
{
    // TODO
}
