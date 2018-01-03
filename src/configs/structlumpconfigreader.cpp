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

    if ( memberType == BSPStructItemTypes::PublicItemType::Array )
    {
        BSPStructItemTypes::PublicItemType arrayType = getPublicType(memberObject, "arraytype");
        coreType = static_cast<BSPStructItemTypes::CoreItemType>(arrayType);

        if ( BSPStructItemTypes::unmodifiedCoreType(coreType) == BSPStructItemTypes::Meta_Array )
        {
            throw JSONReaderException(memberObject->getObjectItem("arraytype")->computePath(),
                                      "Array type cannot be 'array'.");
        }

        itemCount = memberObject->getObjectItemOfType<qint32>("arraycount");
        if ( itemCount < 1 )
        {
            throw JSONReaderException(memberObject->getObjectItem("arraycount")->computePath(),
                                      "Array count must be greater than 0.");
        }
    }

    QSharedPointer<StructMemberConfigReader> memberReader =
            StructMemberConfigReaderFactory::createReader(coreType, m_pStructLumpDef, memberObject);

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
        throw JSONReaderException(memberObject->getObjectItem(key)->computePath(),
                                  QString("'%0' of '%1' was unrecognised.").arg(key).arg(typeString));
    }
}

void StructLumpConfigReader::linkInternal()
{
    // TODO
}
