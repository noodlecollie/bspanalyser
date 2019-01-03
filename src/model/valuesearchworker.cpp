#include "valuesearchworker.h"

#include "bsp/bspfilestructure.h"
#include "bsp/bspdatafragment.h"
#include "model/applicationmodel.h"
#include "bsp/structlumpdef.h"

ValueSearchWorker::ValueSearchWorker(QObject *parent)
    : QObject(parent),
      m_strPropertyName(),
      m_strValueToFind()
{
}

QString ValueSearchWorker::propertyName() const
{
    return m_strPropertyName;
}

void ValueSearchWorker::setPropertyName(const QString& prop)
{
    m_strPropertyName = prop;
}

QString ValueSearchWorker::valueToFind() const
{
    return m_strValueToFind;
}

void ValueSearchWorker::setValueToFind(const QString& val)
{
    m_strValueToFind = val;
}

QVector<ValueSearchWorker::LumpItemPair> ValueSearchWorker::performSearch()
{
    m_SearchResults = QVector<LumpItemPair>();
    BSPFileStructure* fileStructure = ApplicationModel::globalPointer()->bspFileStructure();

    for ( int index = 0; index < fileStructure->lumpDefCount(); ++index )
    {
        processLumpDef(fileStructure->lumpDef(index));
    }

    return m_SearchResults;
}

void ValueSearchWorker::processLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef)
{
    if ( lumpDef->type() != BSPLumpDef::LumpType::Struct )
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
    QByteArray data = dataFragment.data();
    quint32 itemCount = data.count()/lumpDef->bspStruct().size();

    for ( quint32 index = 0; index < itemCount; ++index )
    {
        QByteArray itemData = lumpDef->getDataForItem(data, index);

        // TODO
    }
}
