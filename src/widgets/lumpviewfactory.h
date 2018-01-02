#ifndef LUMPVIEWFACTORY_H
#define LUMPVIEWFACTORY_H

#include <QWidget>
#include <QSharedPointer>

#include "bsp/bsplumpdef.h"
#include "widgets/ilumpviewwidget.h"

class LumpViewFactory
{
public:
    LumpViewFactory(const QSharedPointer<BSPLumpDef>& lumpDef);

    ILumpViewWidget* createWidget() const;

private:
    QSharedPointer<BSPLumpDef> m_pLumpDef;
};

#endif // LUMPVIEWFACTORY_H
