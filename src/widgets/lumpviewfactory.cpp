#include "lumpviewfactory.h"

#include "keyvalueslumpviewwidget.h"

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

        default:
        {
            return nullptr;
        }
    }
}
