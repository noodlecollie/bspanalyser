#ifndef JSONREADEREXCEPTION_H
#define JSONREADEREXCEPTION_H

#include "exceptions/genericexception.h"

class JSONReaderException : public GenericException
{
public:
    JSONReaderException(const QString& path, const QString& message)
        : GenericException(message),
          m_strPath(path)
    {
    }

    virtual void raise() const override
    {
        throw *this;
    }

    virtual QException* clone() const override
    {
        return new JSONReaderException(*this);
    }

    virtual QString message() const override
    {
        return QString("At element '%0': %1").arg(m_strPath).arg(m_strMessage);
    }

    QString path() const
    {
        return m_strPath;
    }

private:
    QString m_strPath;
};

#endif // JSONREADEREXCEPTION_H
