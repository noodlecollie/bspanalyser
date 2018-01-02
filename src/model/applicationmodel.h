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
    ~ApplicationModel();

    static ApplicationModel* globalPointer();

    BSPFileModel* bspFileModel();
    BSPFileStructure* bspFileStructure();
    BSPFormatCollection& bspFormatCollection();

private:
    static ApplicationModel* m_pGlobalModel;

    BSPFileModel* m_pBSPFileModel;
    BSPFileStructure m_BSPFileStructure;
    BSPFormatCollection m_BSPFormatCollection;
};

#endif // APPLICATIONMODEL_H
