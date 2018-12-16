#ifndef BSPDEFS_H
#define BSPDEFS_H

#include <QtGlobal>

namespace BSPDefs
{
    static constexpr quint32 VERSION_BYTES = sizeof(quint32);
    static constexpr quint32 SUBVERSION_BYTES = sizeof(quint32);
    static constexpr quint32 HEADER_LUMP_DEF_BYTES = 2 * sizeof(quint32);
}

#endif // BSPDEFS_H
