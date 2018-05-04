#include "lumpviewfactory.h"

#include "keyvalueslumpviewwidget.h"
#include "visibilitylumpviewwidget.h"
#include "structlumpviewwidget.h"
#include "notimplementedplaceholderwidget.h"

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
            return new KeyValuesLumpViewWidget();
        }

        case BSPLumpDef::LumpType::Struct:
        {
            return new StructLumpViewWidget();
        }

        case BSPLumpDef::LumpType::VisData:
        {
            return new VisibilityLumpViewWidget();
        }

        default:
        {
            return new NotImplementedPlaceholderWidget(QString("Unsupported lump type '%0'.")
                                                       .arg(BSPLumpDef::lumpTypeNameMap().key(m_pLumpDef->type())));
        }
    }
}
