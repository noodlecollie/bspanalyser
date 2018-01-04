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
    BSPStructItemTypes::CoreItemType coreType = static_cast<BSPStructItemTypes::CoreItemType>(memberType);
    qint32 itemCount = 1;

    if ( BSPStructItemTypes::unmodifiedCoreType(coreType) == BSPStructItemTypes::Meta_Array )
    {
        if ( BSPStructItemTypes::coreTypeHasModifier(coreType, BSPStructItemTypes::Mod_InterpretAsString) )
        {
            coreType = BSPStructItemTypes::Type_StringChar;
            itemCount = memberObject->getObjectItemOfType<qint32>("stringsize");

            if ( itemCount < 1 )
            {
                throw memberObject->getObjectItem("stringsize")->createException("String size must be greater than 0.");
            }
        }
        else
        {
            BSPStructItemTypes::PublicItemType arrayType = getPublicType(memberObject, "arraytype");
            coreType = static_cast<BSPStructItemTypes::CoreItemType>(arrayType);

            if ( BSPStructItemTypes::unmodifiedCoreType(coreType) == BSPStructItemTypes::Meta_Array )
            {
                throw memberObject->getObjectItem("arraytype")->createException("Array type cannot be 'array'.");
            }

            if ( BSPStructItemTypes::unmodifiedCoreType(coreType) == BSPStructItemTypes::Type_String )
            {
                throw memberObject->getObjectItem("arraytype")->createException("Array type cannot be 'string'.");
            }

            itemCount = memberObject->getObjectItemOfType<qint32>("arraycount");
            if ( itemCount < 1 )
            {
                throw memberObject->getObjectItem("arraycount")->createException("Array count must be greater than 0.");
            }
        }
    }

    QSharedPointer<StructMemberConfigReader> memberReader =
            StructMemberConfigReaderFactory::createReader(coreType, m_pStructLumpDef, memberObject, static_cast<quint32>(itemCount));

    BSPStructGenericBlock* member = memberReader->loadAndCreateMember();
    Q_ASSERT(member);

    member->setName(memberName);
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
