#include "structmemberconfigreaderfactory.h"

#include "structmemberconfigreader_simple.h"
#include "structmemberconfigreader_integer.h"

namespace StructMemberConfigReaderFactory
{
    QSharedPointer<StructMemberConfigReader> createReader(BSPStructItemTypes::CoreItemType type,
                                                          const QSharedPointer<StructLumpDef>& structLumpDef,
                                                          const JSONReaderItemPtr& memberObject,
                                                          quint32 count)
    {
        StructMemberConfigReader* reader = nullptr;

        // Then unmodified types.
        if ( !reader )
        {
            switch ( BSPStructItemTypes::unmodifiedCoreType(type) )
            {
                case BSPStructItemTypes::Type_Int8:
                case BSPStructItemTypes::Type_Int16:
                case BSPStructItemTypes::Type_Int32:
                {
                    reader = new StructMemberConfigReader_Integer(type, structLumpDef, memberObject, count);
                    break;
                }

                default:
                {
                    reader = new StructMemberConfigReader_Simple(type, structLumpDef, memberObject, count);
                    break;
                }
            }
        }

        return QSharedPointer<StructMemberConfigReader>(reader);
    }
}
