#ifndef READEREXCEPTION_H
#define READEREXCEPTION_H

#include <QException>

class ReaderException : public QException
{
public:
    ReaderException(const QString& inMessage)
        : QException(),
          m_strMessage(inMessage)
    {

    }

    virtual void raise() const override
    {
        throw *this;
    }

    virtual ReaderException* clone() const override
    {
        return new ReaderException(*this);
    }

    const QString& message() const
    {
        return m_strMessage;
    }

private:
    QString m_strMessage;
};

#endif // READEREXCEPTION_H
