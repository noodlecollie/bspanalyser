#ifndef IBSPDATAITEM_H
#define IBSPDATAITEM_H

#include "bspdatafragment.h"

class BSPFileModel;

class IBSPDataItem
{
public:
    virtual ~IBSPDataItem() {}

    virtual BSPDataFragment getDataFragment(const BSPFileModel& data) const = 0;
};

#endif // IBSPDATAITEM_H
