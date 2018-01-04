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
        Mod_InterpretAsString = (1 << 10),

        // ================
        // Unmodified Types
        // ================

        Type_Invalid = 0,

        // Primitives
        Type_Int8 = 1,
        Type_Int16 = 2,
        Type_Int32 = 3,
        Type_Float = 4,

        // Tuples
        Type_FVector3 = 5,
        Type_FVector4 = 6,
        Type_RGB8 = 7,
        Type_FVector3AABB = 8,

        // Meta - depend on further config data for type resolution
        Meta_Array = 9,

        // ==============
        // Modified Types
        // ==============

        Type_UInt8 = Type_Int8 | Mod_IsUnsigned,
        Type_UInt16 = Type_Int16 | Mod_IsUnsigned,
        Type_UInt32 = Type_Int32 | Mod_IsUnsigned,

        Type_PrimaryIndex32 = Type_UInt32 | Mod_IsPrimaryIndex,
        Type_PrimaryOffset32 = Type_UInt32 | Mod_IsPrimaryOffset,
        Type_SecondaryIndex32 = Type_UInt32 | Mod_IsSecondaryIndex,
        Type_BinaryIndex32 = Type_Int32 | Mod_IsBinaryIndex,

        Type_String = Meta_Array | Mod_InterpretAsString,
        Type_StringChar = Type_Int8 | Mod_InterpretAsString,

        //-------------------------------

        // Max legal type index.
        // Any bits above this mask are reserved for modifiers.
        Mask_LegalType = 31,
    };

    // In a clean, meta-object-exposed enum to avoid all the implementation
    // bitmashing that goes on in the other enum.
    // Each entry MUST correspond to a CoreItemType.
    // Only types here are allowed to be specified in a format document.
    enum class PublicItemType
    {
        Int8 = Type_Int8,
        Int16 = Type_Int16,
        Int32 = Type_Int32,
        UInt8 = Type_UInt8,
        UInt16 = Type_UInt16,
        UInt32 = Type_UInt32,
        Float = Type_Float,

        PrimaryIndex32 = Type_PrimaryIndex32,
        PrimaryOffset32 = Type_PrimaryOffset32,
        SecondaryIndex32 = Type_SecondaryIndex32,
        BinaryIndex32 = Type_BinaryIndex32,

        Vector3 = Type_FVector3,
        Vector4 = Type_FVector4,
        Vector3AABB = Type_FVector3AABB,
        RGB8 = Type_RGB8,

        String = Type_String,
        Array = Meta_Array,
    };
    Q_ENUM(PublicItemType)

    static const EnumNameMap<PublicItemType> publicItemTypeNameMap();

    static constexpr CoreItemType unmodifiedCoreType(CoreItemType type)
    {
        return static_cast<CoreItemType>(type & Mask_LegalType);
    }

    static constexpr bool coreTypeHasModifier(CoreItemType type, CoreItemType modifier)
    {
        return type & modifier;
    }

    static quint32 sizeOfCoreType(CoreItemType type);
};

#endif // BSPSTRUCTITEMTYPES_H
