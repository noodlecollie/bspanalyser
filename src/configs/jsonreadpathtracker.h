#ifndef JSONREADPATHTRACKER_H
#define JSONREADPATHTRACKER_H

#include <QString>
#include <QStack>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSharedPointer>

#include "jsonreadpathtrackeritem.h"

class JSONReadPathTracker
{
public:
    JSONReadPathTracker();
    JSONReadPathTracker(const QJsonDocument& document);

    const QJsonDocument* document() const;

    QString currentPath() const;

    QString cachedPath() const;
    void cacheCurrentPath();

    void pushPathSegment(const QString& segment);
    void popPathSegment();

    QSharedPointer<JSONReadPathTrackerItem> getRootObjectItem();
    QSharedPointer<JSONReadPathTrackerItem> getRootArrayItem();

private:
    const QJsonDocument* m_pDocument;
    QStack<QString> m_stackPath;
    QString m_strCachedPath;
};

#endif // JSONREADPATHTRACKER_H
