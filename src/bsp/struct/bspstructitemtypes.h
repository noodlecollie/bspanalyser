#ifndef BSPSTRUCTITEMTYPES_H
#define BSPSTRUCTITEMTYPES_H

#include <QObject>

#include "util/enumnamemap.h"

/*
 * Notable item types:
 *
 * PrimaryIndex         1x UInt32. Indexes one item in a separate lump. The lump must be of
 *                      type Struct.
 * PrimaryOffset        1x UInt32. Indexes bytewise into any other lump.
 * SecondaryIndex       1x UInt32. Indexes a list of items generated dynamically. For example,
 *                      Nightfire BSPs first index a block of vertices from the Vertices lump,
 *                      and then draw indices act as indices into this new block. The secondary
 *                      index mapping is specified by the lump that requires it, using the
 *                      "secondaryindexmapping" attribute.
 * BinaryIndex          1x UInt32. Indexes one of two Struct lumps, depending on whether the
 *                      index is positive or negative. A negative index N is treated as (-N) - 1.
 * PrimaryIndexBlock    2x UInt32. Indexes one or more items in a separate Struct lump. The first
 *                      number is the item offset and the second is the item count.
 * Array                Specifies several consecutive types in the same lump. The array must
 *                      specify an item type and count. Currently the item type can only be
 *                      primitive.
 * String               An array of chars of a known length. Null-terminated strings are not
 *                      currently supported.
 * Vector3AABB          2x Vector3. Used to specify an axially-aligned bounding box.
 *
 * In addition, an Int32 member can specify an "enum" option which should reference a defined enum
 * in the format file. Instead of numerical values, the enum named values will be displayed instead.
 */

class BSPStructItemTypes
{
    Q_GADGET
public:
    enum CoreItemType
    {
        // Modifiers
        Mod_IsUnsigned = (1 << 5),
        Mod_IsPrimaryIndex = (1 << 6),
        Mod_IsPrimaryOffset = (1 << 7),
        Mod_IsSecondaryIndex = (1 << 8),
        Mod_IsBinaryIndex = (1 << 9),
        Mod_IsArray = (1 << 10),

        // ================
        // Unmodified Types
        // ================

        // Primitives
        Type_Int8 = 0,
        Type_Int16 = 1,
        Type_Int32 = 2,
        Type_Float = 3,

        // Tuples
        Type_FVector3 = 5,
        Type_FVector4 = 6,
        Type_RGB8 = 7,
        Type_Int32Pair = 8,
        Type_FVector3AABB = 9,

        // ==============
        // Modified Types
        // ==============

        Type_UInt8 = Type_Int8 | Mod_IsUnsigned,
        Type_UInt16 = Type_Int16 | Mod_IsUnsigned,
        Type_UInt32 = Type_Int32 | Mod_IsUnsigned,

        Type_PrimaryIndex32 = Type_UInt32 | Mod_IsPrimaryIndex,
        Type_PrimaryOffset32 = Type_UInt32 | Mod_IsPrimaryOffset,
        Type_SecondaryIndex32 = Type_UInt32 | Mod_IsSecondaryIndex,
        Type_BinaryIndex32 = Type_UInt32 | Mod_IsBinaryIndex,
        Type_PrimaryIndexBlock32 = Type_Int32Pair | Mod_IsUnsigned | Mod_IsPrimaryIndex,

        //-------------------------------

        // Max legal type index.
        // Any bits above this mask are reserved for modifiers.
        Mask_LegalType = 31,
    };

    static constexpr CoreItemType unmodifiedCoreType(CoreItemType type)
    {
        return static_cast<CoreItemType>(type & Mask_LegalType);
    }

    static quint32 sizeOfCoreType(CoreItemType type);
};

#endif // BSPSTRUCTITEMTYPES_H
