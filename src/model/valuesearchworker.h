#ifndef VALUESEARCHWORKER_H
#define VALUESEARCHWORKER_H

#include <QObject>
#include <QString>
#include <QPair>
#include <QSharedPointer>
#include <QVector>

class BSPLumpDef;
class StructLumpDef;

class ValueSearchWorker : public QObject
{
    Q_OBJECT
public:
    struct SearchResult
    {
        quint32 lumpIndex;
        QString lumpName;
        quint32 itemIndex;

        SearchResult(quint32 lumpIndex, const QString& lumpName, quint32 itemIndex)
            : lumpIndex(lumpIndex),
              lumpName(lumpName),
              itemIndex(itemIndex)
        {
        }

        SearchResult()
            : lumpIndex(0),
              lumpName(),
              itemIndex(0)
        {
        }
    };

    ValueSearchWorker(QObject* parent = Q_NULLPTR);

    QVector<SearchResult> performSearch(const QString& propertyName, const QString& matchValue, const QVector<QString>& lumpNames);

private:
    void processLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef, const QVector<QString>& lumpNames);
    void processValuesForMatchingMembers(const QSharedPointer<StructLumpDef>& lumpDef, const QVector<int>& memberIndices);

    QString m_strPropertyName;
    QString m_strValueToFind;
    QVector<SearchResult> m_SearchResults;
};

#endif // VALUESEARCHWORKER_H
