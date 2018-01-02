#ifndef ENUMVALUENOTFOUNDEXCEPTION_H
#define ENUMVALUENOTFOUNDEXCEPTION_H

#include <QException>

// In its own file, so it doesn't depend on the templated type of the EnumNameMap.
class EnumValueNotFoundException : public QException
{
public:
    virtual void raise() const override
    {
        throw *this;
    }
    virtual QException *clone() const override
    {
        return new EnumValueNotFoundException(*this);
    }
};

#endif // ENUMVALUENOTFOUNDEXCEPTION_H
