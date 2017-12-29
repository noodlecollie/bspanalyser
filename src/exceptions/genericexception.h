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

    virtual QException* clone() const override
    {
        return new GenericException(*this);
    }

    virtual QString message() const
    {
        return m_strMessage;
    }

protected:
    QString m_strMessage;
};

#endif // GENERICEXCEPTION_H
