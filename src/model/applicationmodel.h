#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QObject>

#include "bspfilemodel.h"
#include "bsp/bspfilestructure.h"
#include "configs/bspformatcollection.h"

class ApplicationModel : public QObject
{
    Q_OBJECT
public:
    ApplicationModel(QObject* parent = nullptr);

    BSPFileModel* bspFileModel();
    BSPFileStructure* bspFileStructure();
    BSPFormatCollection& bspFormatCollection();

private:
    BSPFileModel* m_pBSPFileModel;
    BSPFileStructure m_BSPFileStructure;
    BSPFormatCollection m_BSPFormatCollection;
};

#endif // APPLICATIONMODEL_H
