#include "valuesearchworker.h"

#include "bsp/bspfilestructure.h"
#include "bsp/bspdatafragment.h"
#include "bsp/structlumpdef.h"
#include "bsp/displaystringconversion.h"
#include "model/applicationmodel.h"

ValueSearchWorker::ValueSearchWorker(QObject *parent)
    : QObject(parent),
      m_strPropertyName(),
      m_strValueToFind()
{
}

QVector<ValueSearchWorker::LumpItemPair> ValueSearchWorker::performSearch(const QString& propertyName, const QString& matchValue, const QVector<QString>& lumpNames)
{
    m_strPropertyName = propertyName;
    m_strValueToFind = matchValue;

    m_SearchResults = QVector<LumpItemPair>();
    BSPFileStructure* fileStructure = ApplicationModel::globalPointer()->bspFileStructure();

    for ( int index = 0; index < fileStructure->lumpDefCount(); ++index )
    {
        processLumpDef(fileStructure->lumpDef(index), lumpNames);
    }

    return m_SearchResults;
}

void ValueSearchWorker::processLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef, const QVector<QString>& lumpNames)
{
    if ( lumpDef->type() != BSPLumpDef::LumpType::Struct || !lumpNames.contains(lumpDef->name()) )
    {
        return;
    }

    QSharedPointer<StructLumpDef> structLumpDef = lumpDef.staticCast<StructLumpDef>();
    BSPStruct& bspStruct = structLumpDef->bspStruct();
    QVector<int> matchingMembers;

    for ( int index = 0; index < bspStruct.memberCount(); ++index )
    {
        BSPStructGenericBlock* member = bspStruct.member(index);
        if ( member->name() == m_strPropertyName )
        {
            matchingMembers.append(index);
        }
    }

    if ( matchingMembers.isEmpty() )
    {
        return;
    }

    processValuesForMatchingMembers(structLumpDef, matchingMembers);
}

void ValueSearchWorker::processValuesForMatchingMembers(const QSharedPointer<StructLumpDef>& lumpDef, const QVector<int>& memberIndices)
{
    BSPFileModel* fileModel = ApplicationModel::globalPointer()->bspFileModel();
    BSPDataFragment dataFragment = lumpDef->getDataFragment(*fileModel);
    QByteArray lumpData = dataFragment.data();
    quint32 itemCount = static_cast<quint32>(lumpData.count())/lumpDef->bspStruct().size();

    for ( quint32 itemIndex = 0; itemIndex < itemCount; ++itemIndex )
    {
        for ( int memberIndex : memberIndices )
        {
            QString displayString = DisplayStringConversion::displayStringForMember(*lumpDef, lumpData, itemIndex, static_cast<quint32>(memberIndex));
            if ( displayString == m_strValueToFind )
            {
                m_SearchResults.append(LumpItemPair(lumpDef->name(), itemIndex));

                // We don't want to add this item to the search results more than once,
                // so return as soon as one of the members matches.
                return;
            }
        }
    }
}
