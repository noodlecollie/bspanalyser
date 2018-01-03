#ifndef BSPSTRUCTITEM_H
#define BSPSTRUCTITEM_H

#include <QObject>
#include <QVariant>

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
 *                      specify an item type (which can be any type other than another array)
 *                      and an item count.
 * String               An array of chars of a known length. Null-terminated strings are not
 *                      currently supported.
 * Vector3AABB          2x Vector3. Used to specify an axially-aligned bounding box.
 *
 * In addition, an Int32 member can specify an "enum" option which should reference a defined enum
 * in the format file. Instead of numerical values, the enum named values will be displayed instead.
 */

class BSPStruct;

class BSPStructItem : public QObject
{
    Q_OBJECT
public:
    // This enum must contain all possible strings that could occur in a format document.
    enum class ItemType
    {
        Invalid = 0,

        // Primitives
        Int8 = 1,
        Int16 = 2,
        Int32 = 3,
        Float = 4,
        String = 5,

        // Primitives with semantics
        PrimaryIndex = 6,
        PrimaryOffset = 7,
        SecondaryIndex = 8,
        BinaryIndex = 9,

        // Tuples
        Vector3 = 10,
        Vector4 = 11,
        RGB8 = 12,
        PrimaryIndexBlock = 13,

        // Aggregates
        Array = 14,
        Vector3AABB = 15,

        // Max legal type index: 63
        Mask_LegalType = 63,

        // Modifiers
        Mod_IsUnsigned = (1 << 6),

        // Convenience combinations
        UInt8 = Int8 | Mod_IsUnsigned,
        UInt16 = Int16 | Mod_IsUnsigned,
        UInt32 = Int32 | Mod_IsUnsigned,
    };
    Q_ENUM(ItemType)

    static const EnumNameMap<ItemType>& itemTypeNameMap();

    static constexpr bool typeIsValid(ItemType type)
    {
        return static_cast<ItemType>(static_cast<quint32>(type) & static_cast<quint32>(ItemType::Mask_LegalType))
                != ItemType::Invalid;
    }

    static constexpr bool typeIsUnsigned(ItemType type)
    {
        return (static_cast<quint32>(type) & static_cast<quint32>(ItemType::Mod_IsUnsigned))
                == static_cast<quint32>(ItemType::Mod_IsUnsigned);
    }

    static constexpr bool typeIsValidForConstruction(ItemType type)
    {
        return type != ItemType::Invalid &&
                type != ItemType::Mask_LegalType &&
                type != ItemType::Mod_IsUnsigned;
    }

    BSPStruct* parentStruct() const;
    quint32 offsetInParent() const;
    ItemType type() const;

    // Size of the entire member itself, in bytes.
    // For arrays, this is item count * item size.
    virtual quint32 size() const = 0;

protected:
    BSPStructItem(BSPStruct* parent, ItemType type);

private:
    friend class BSPStruct;

    void setOffsetInParent(quint32 offset);

    ItemType m_nType;
    quint32 m_nOffsetInParent;
};

#endif // BSPSTRUCTITEM_H
