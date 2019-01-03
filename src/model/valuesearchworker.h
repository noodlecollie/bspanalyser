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
    typedef QPair<QString, quint32> LumpItemPair;

    ValueSearchWorker(QObject* parent = Q_NULLPTR);

    QString propertyName() const;
    void setPropertyName(const QString& prop);

    QString valueToFind() const;
    void setValueToFind(const QString& val);

    QVector<LumpItemPair> performSearch();

private:
    void processLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef);
    void processValuesForMatchingMembers(const QSharedPointer<StructLumpDef>& lumpDef, const QVector<int>& memberIndices);

    QString m_strPropertyName;
    QString m_strValueToFind;
    QVector<LumpItemPair> m_SearchResults;
};

#endif // VALUESEARCHWORKER_H
