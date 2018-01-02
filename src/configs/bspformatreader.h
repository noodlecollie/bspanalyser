#ifndef BSPFORMATREADER_H
#define BSPFORMATREADER_H

#include <QJsonDocument>
#include <QSharedPointer>

#include "bsp/bspfilestructure.h"
#include "bsp/bsplumpdef.h"
#include "bsp/visibilitylumpdef.h"
#include "bsp/structlumpdef.h"
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

    // First-time reading
    void readAllLumps(const JSONReaderItemPtr& lumpsList, const JSONReaderItemPtr& lumpItemsObject);
    QSharedPointer<BSPLumpDef> readLumpData(const QString& lumpName, const JSONReaderItemPtr& lumpItemsObject);
    void readLumpData(const QSharedPointer<VisibilityLumpDef>& lump, const JSONReaderItemPtr& lumpJson);
    void readLumpData(const QSharedPointer<StructLumpDef>& lump, const JSONReaderItemPtr& lumpJson);

    // Post-read linking
    void linkLumps(const JSONReaderItemPtr& lumpItemsObject);
    void linkLump(const QSharedPointer<VisibilityLumpDef>& lump, const JSONReaderItemPtr& lumpJson);
    void linkLump(const QSharedPointer<StructLumpDef>& lump, const JSONReaderItemPtr& lumpJson);

    // Expected to be valid when calling private reading functions.
    BSPFileStructure* m_pCurrentFile;
};

#endif // BSPFORMATREADER_H
