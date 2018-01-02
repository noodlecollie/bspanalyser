#include "lumpviewfactory.h"

#include "keyvalueslumpviewwidget.h"
#include "visibilitylumpviewwidget.h"

LumpViewFactory::LumpViewFactory(const QSharedPointer<BSPLumpDef> &lumpDef)
    : m_pLumpDef(lumpDef)
{

}

ILumpViewWidget* LumpViewFactory::createWidget() const
{
    if ( !m_pLumpDef )
    {
        return nullptr;
    }

    switch ( m_pLumpDef->type() )
    {
        case BSPLumpDef::LumpType::Keyvalues:
        {
            return new KeyvaluesLumpViewWidget();
        }

        case BSPLumpDef::LumpType::VisData:
        {
            return new VisibilityLumpViewWidget();
        }

        default:
        {
            return nullptr;
        }
    }
}
