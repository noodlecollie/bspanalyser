#include "applicationmodel.h"

ApplicationModel* ApplicationModel::m_pGlobalModel = nullptr;

ApplicationModel::ApplicationModel(QObject* parent)
    : QObject(parent),
      m_pBSPFileModel(new BSPFileModel(this)),
      m_BSPFileStructure(),
      m_BSPFormatCollection()
{
    Q_ASSERT(!m_pGlobalModel);
    m_pGlobalModel = this;

    m_BSPFormatCollection.initialise();
}

ApplicationModel::~ApplicationModel()
{
    Q_ASSERT(m_pGlobalModel);
    m_pGlobalModel = nullptr;
}

ApplicationModel* ApplicationModel::globalPointer()
{
    Q_ASSERT(m_pGlobalModel);
    return m_pGlobalModel;
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
