#include "applicationmodel.h"

ApplicationModel::ApplicationModel(QObject* parent)
    : QObject(parent),
      m_pBSPFileModel(new BSPFileModel(this)),
      m_BSPFileStructure(),
      m_BSPFormatCollection()
{
    m_BSPFormatCollection.initialise();
}

BSPFileModel* ApplicationModel::bspFileModel()
{
    return m_pBSPFileModel;
}

BSPFileStructure* ApplicationModel::bspFileStructure()
{
    return &m_BSPFileStructure;
}

BSPFormatCollection& ApplicationModel::bspFormatCollection()
{
    return m_BSPFormatCollection;
}
