#ifndef BSPFORMATREADER_H
#define BSPFORMATREADER_H

#include <QJsonDocument>

#include "bsp/bspfilestructure.h"

#include "jsonreadpathtracker.h"

class BSPFormatReader
{
public:
    BSPFormatReader();

    bool read(const QJsonDocument& document, BSPFileStructure& outFile, QString& error);
    quint32 readVersion(const QJsonDocument& document, QString& error);

private:
    quint32 readVersionInternal(JSONReadPathTracker& json);
    void readJsonDocument(JSONReadPathTracker& json);
    void readLumpList(const QSharedPointer<JSONReadPathTrackerItem>& root);

    // Expected to be valid when calling private reading functions.
    BSPFileStructure* m_pCurrentFile;
    JSONReadPathTracker m_JsonTracker;
};

#endif // BSPFORMATREADER_H
