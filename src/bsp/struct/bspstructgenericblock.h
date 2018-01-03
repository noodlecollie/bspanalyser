#ifndef BSPSTRUCTGENERICBLOCK_H
#define BSPSTRUCTGENERICBLOCK_H

#include <QByteArray>

#include "exceptions/bspstructexceptions.h"

class BSPStructGenericBlock
{
public:
    BSPStructGenericBlock(quint32 inOffset, quint32 inItemSize, quint32 inItemCount);

    quint32 offset() const;
    void setOffset(quint32 newOffset);

    quint32 itemSize() const;
    void setItemSize(quint32 newSize);

    quint32 itemCount() const;
    void setItemCount(quint32 newCount);

    quint32 totalSize() const;

    // *Technically* T doesn't have to be the same size as the item being requested.
    // If it's not, you'd better know what you're doing.
    template<typename T>
    T item(const QByteArray& data, quint32 index = 0) const
    {
        if ( index >= m_nItemCount )
        {
            throw BSPStructOutOfRangeException(BSPStructOutOfRangeException::Type::Index,
                                               index,
                                               itemCount());
        }

        quint32 offset = m_nOffsetInStruct + (index * m_nItemSize);
        quint32 end = offset + qMax<quint32>(m_nItemSize, sizeof(T));

        if ( end > static_cast<quint32>(data.length()) )
        {
            throw BSPStructOutOfRangeException(BSPStructOutOfRangeException::Type::Offset,
                                               end,
                                               data.length());
        }

        const char* itemAsChar = data.constData() + offset;
        return *(reinterpret_cast<const T*>(itemAsChar));
    }

private:
    quint32 m_nOffsetInStruct;
    quint32 m_nItemSize;
    quint32 m_nItemCount;
};

#endif // BSPSTRUCTGENERICBLOCK_H
