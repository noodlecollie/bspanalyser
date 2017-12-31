#include "lumpviewfactory.h"

// TODO: Remove me when implemented properly.
#include <QLabel>

LumpViewFactory::LumpViewFactory(const QSharedPointer<BSPLumpDef> &lumpDef)
    : m_pLumpDef(lumpDef)
{

}

QWidget* LumpViewFactory::createWidget() const
{
    if ( !m_pLumpDef )
    {
        return nullptr;
    }

    switch ( m_pLumpDef->type() )
    {
        case BSPLumpDef::LumpType::Keyvalues:
        {
            // TODO
            return new QLabel("This is the view widget for Keyvalues lumps.");
        }

        default:
        {
            return nullptr;
        }
    }
}
