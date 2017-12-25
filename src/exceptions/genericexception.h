#ifndef GENERICEXCEPTION_H
#define GENERICEXCEPTION_H

#include <QException>

class GenericException : public QException
{
public:
    GenericException(const QString& message)
        : QException(),
          m_strMessage(message)
    {

    }

    virtual void raise() const override
    {
        throw *this;
    }

    virtual GenericException* clone() const override
    {
        return new GenericException(*this);
    }

    const QString& message() const
    {
        return m_strMessage;
    }

private:
    QString m_strMessage;
};

#endif // GENERICEXCEPTION_H
