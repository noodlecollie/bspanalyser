#ifndef BSPFORMATREADER_H
#define BSPFORMATREADER_H

#include <QJsonDocument>
#include <QSharedPointer>

#include "bsp/bspfilestructure.h"
#include "bsp/bsplumpdef.h"
#include "bsp/visibilitylumpdef.h"
#include "bsp/structlumpdef.h"
#include "configs/jsonreaderitem.h"
#include "configs/abstractlumpconfigreader.h"

class BSPFormatReader
{
public:
    BSPFormatReader();

    bool read(const QJsonDocument& document, BSPFileStructure& outFile, QString& error);
    quint32 readVersion(const QJsonDocument& document, QString& error);
    bool readSubVersion(const QJsonDocument& document, quint32& subVersion, QString& error);

private:
    quint32 readVersionInternal(const QJsonDocument& document);
    quint32 readSubVersionInternal(const QJsonDocument& document);
    void readJsonDocument(const QJsonDocument& document);
    void readLumpList(const JSONReaderItemPtr& root);
    void readAllLumps(const JSONReaderItemPtr& lumpsList, const JSONReaderItemPtr& lumpItemsObject);
    void linkLumps();

    // Expected to be valid when calling private reading functions.
    BSPFileStructure* m_pCurrentFile;
    QVector<QSharedPointer<AbstractLumpConfigReader>> m_liLumpReaders;
};

#endif // BSPFORMATREADER_H
