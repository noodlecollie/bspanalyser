#ifndef BSPSTRUCTEXCEPTIONS_H
#define BSPSTRUCTEXCEPTIONS_H

#include <QException>

class BSPStructOutOfRangeException : public QException
{
public:
    enum class Type
    {
        Index,  // Eg. Index is off the end of the array.
        Offset  // If the struct data itself is smaller than the requested index.
    };

    BSPStructOutOfRangeException(Type type, quint32 given, quint32 max)
        : m_nType(type),
          m_nGivenBound(given),
          m_nMaxBound(max)
    {
    }

    Type type() const
    {
        return m_nType;
    }

    quint32 givenBound() const
    {
        return m_nGivenBound;
    }

    quint32 maxBound() const
    {
        return m_nMaxBound;
    }

    virtual void raise() const override
    {
        throw *this;
    }
    virtual QException *clone() const override
    {
        return new BSPStructOutOfRangeException(*this);
    }

private:
    Type m_nType;
    quint32 m_nGivenBound;
    quint32 m_nMaxBound;
};

#endif // BSPSTRUCTEXCEPTIONS_H
