#ifndef IBSPDATAITEM_H
#define IBSPDATAITEM_H

#include "bspdatafragment.h"

class IBSPDataItem
{
public:
    virtual ~IBSPDataItem() {}

    virtual BSPDataFragment getDataFragment(const QByteArray& data) const = 0;
};

#endif // IBSPDATAITEM_H
