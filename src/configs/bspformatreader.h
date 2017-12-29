#ifndef BSPFORMATREADER_H
#define BSPFORMATREADER_H

#include <QJsonDocument>

#include "bsp/bspfilestructure.h"
#include "configs/jsonreaderitem.h"

class BSPFormatReader
{
public:
    BSPFormatReader();

    bool read(const QJsonDocument& document, BSPFileStructure& outFile, QString& error);
    quint32 readVersion(const QJsonDocument& document, QString& error);

private:
    quint32 readVersionInternal(const QJsonDocument& document);
    void readJsonDocument(const QJsonDocument& document);
    void readLumpList(const JSONReaderItemPtr& root);
    void readLumpData(const QSharedPointer<BSPLumpDef>& lumpDef,
                      const JSONReaderItemPtr& lumpItemsObject);

    // Expected to be valid when calling private reading functions.
    BSPFileStructure* m_pCurrentFile;
};

#endif // BSPFORMATREADER_H
