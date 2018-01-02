#include "keyvaluesjsonconverter.h"

#include "exceptions/genericexception.h"

namespace
{
    static constexpr const char* STATE_NAMES[] =
    {
        "OutsideObject",
        "InObject",
        "InKey",
        "BetweenKeyAndValue",
        "InValue",
    };

    static bool isWhitespace(char ch)
    {
        return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
    }

    static const char* charAsTempString(char ch)
    {
        static char tinyString[2] = { '\0', '\0' };

        tinyString[0] = ch;
        return tinyString;
    }
}

class KeyValuesJsonConverter::EndOfInputException : public QException
{
public:
    EndOfInputException(KeyValuesJsonConverter::ParseState state)
        : QException(),
          m_nState(state)
    {
    }

    virtual void raise() const override
    {
        throw *this;
    }

    virtual QException* clone() const override
    {
        return new EndOfInputException(*this);
    }

    KeyValuesJsonConverter::ParseState state() const
    {
        return m_nState;
    }

private:
    KeyValuesJsonConverter::ParseState m_nState;
};

KeyValuesJsonConverter::KeyValuesJsonConverter()
    : m_pIn(nullptr),
      m_pOut(nullptr),
      m_nInIndex(0),
      m_nOutIndex(0),
      m_nState(ParseState::OutsideObject),
      m_bCreatedObject(false),
      m_bCreatedKVPairInObject(false)
{

}

bool KeyValuesJsonConverter::convert(const QByteArray &inKV, QByteArray &outJSON, QString &errorString)
{
    bool success = false;
    m_pIn = &inKV;
    m_pOut = &outJSON;

    initForParsing();

    try
    {
        convertKeyValuesToJSON();
        success = true;
    }
    catch(GenericException& exception)
    {
        errorString = exception.message();
        outJSON.clear();
    }

    m_pIn = nullptr;
    m_pOut = nullptr;
    return success;
}

void KeyValuesJsonConverter::initForParsing()
{
    m_nInIndex = 0;
    m_nOutIndex = 0;
    m_bCreatedObject = false;
    m_bCreatedKVPairInObject = false;
    m_nState = ParseState::OutsideObject;

    m_pOut->clear();
}

void KeyValuesJsonConverter::convertKeyValuesToJSON()
{
    // Resize out to be as long as in.
    // This will minimise the amount we need to allocate/resize out.
    m_pOut->resize(m_pIn->length());

    // Begin by opening the root JSON array.
    copyOut('[');

    try
    {
        // We break out of this loop when the EndOfInputException is thrown.
        while (true)
        {
            switch (m_nState)
            {
                case ParseState::OutsideObject:
                {
                    skipWhitespace();
                    openObject();

                    m_nState = ParseState::InObject;
                    break;
                }

                case ParseState::InObject:
                {
                    skipWhitespace();

                    ParseState nextState = ParseState::OutsideObject;
                    if ( decideNextActionInObject(nextState) && (nextState == ParseState::InKey || nextState == ParseState::OutsideObject) )
                    {
                        if ( nextState == ParseState::InKey )
                        {
                            if ( m_bCreatedKVPairInObject )
                            {
                                copyOut(',');
                            }

                            openQuotedString();
                        }
                        else
                        {
                            closeObject();
                            m_bCreatedObject = true;
                            m_bCreatedKVPairInObject = false;
                        }
                    }
                    else
                    {
                        raiseExceptionAtCurrentIndex(QString("Expected '{' or '\"' but got '%0'.").arg(charAsTempString((*m_pIn)[m_nInIndex])));
                    }

                    m_nState = nextState;
                    break;
                }

                case ParseState::InKey:
                {
                    skipAllButNonEscapedQuotes();
                    closeQuotedString();

                    m_nState = ParseState::BetweenKeyAndValue;
                    break;
                }

                case ParseState::BetweenKeyAndValue:
                {
                    skipWhitespace();
                    copyOut(':');
                    openQuotedString();

                    m_nState = ParseState::InValue;
                    break;
                }

                case ParseState::InValue:
                {
                    skipAllButNonEscapedQuotes();
                    closeQuotedString();
                    m_bCreatedKVPairInObject = true;

                    m_nState = ParseState::InObject;
                    break;
                }

                default:
                {
                    raiseExceptionAtCurrentIndex(QString("Unexpected parse state '%0' encountered.").arg(static_cast<qint32>(m_nState)));
                }
            }
        }
    }
    catch (EndOfInputException& exception)
    {
        if ( exception.state() != ParseState::OutsideObject )
        {
            raiseExceptionAtCurrentIndex(QString("End of input reached while still in parse state '%0'.").arg(STATE_NAMES[static_cast<qint32>(exception.state())]));
        }
    }

    // Close the root array.
    copyOut(']');
}

bool KeyValuesJsonConverter::decideNextActionInObject(ParseState& state)
{
    validateInputIndex();

    char nextChar = (*m_pIn)[m_nInIndex];

    if ( nextChar == '"' )
    {
        state = ParseState::InKey;
        return true;
    }
    else if ( nextChar == '}' )
    {
        state = ParseState::OutsideObject;
        return true;
    }

    return false;
}

void KeyValuesJsonConverter::copyOut(const char* data, quint32 dataLength, quint32 offset, quint32 length)
{
    quint32 newBound = offset + length;
    quint32 oldBound = m_pOut->length();

    if ( newBound > dataLength )
    {
        newBound = dataLength;
        length = newBound - offset;
    }

    if ( newBound > oldBound )
    {
        m_pOut->resize(newBound);
    }

    for (quint32 index = 0; index < length; ++index)
    {
        (*m_pOut)[m_nOutIndex++] = data[offset + index];
    }
}

void KeyValuesJsonConverter::copyOut(quint32 offset, quint32 length)
{
    copyOut(m_pIn->constData(), m_pIn->length(), offset, length);
}

void KeyValuesJsonConverter::copyOut(const char* data, quint32 dataLength)
{
    copyOut(data, dataLength, 0, dataLength);
}

void KeyValuesJsonConverter::copyOut(char data)
{
    copyOut(&data, 1);
}

void KeyValuesJsonConverter::raiseExceptionAtCurrentIndex(const QString &message)
{
    throw GenericException(QString("Input character %0: %1").arg(m_nInIndex).arg(message));
}

char KeyValuesJsonConverter::consumeChar()
{
    return (*m_pIn)[m_nInIndex++];
}

void KeyValuesJsonConverter::validateInputIndex()
{
    if ( m_nInIndex >= static_cast<quint32>(m_pIn->length()) || !(*m_pIn)[m_nInIndex] )
    {
        throw EndOfInputException(m_nState);
    }
}

void KeyValuesJsonConverter::skipWhitespace()
{
    validateInputIndex();

    while ( m_nInIndex < static_cast<quint32>(m_pIn->length()) && isWhitespace((*m_pIn)[m_nInIndex]) )
    {
        copyOut((*m_pIn)[m_nInIndex]);
        ++m_nInIndex;
    }
}

void KeyValuesJsonConverter::skipAllButNonEscapedQuotes()
{
    validateInputIndex();

    while ( m_nInIndex < static_cast<quint32>(m_pIn->length()) && ((*m_pIn)[m_nInIndex] != '"' || (m_nInIndex > 0 && (*m_pIn)[m_nInIndex - 1] == '\\')) )
    {
        copyOut((*m_pIn)[m_nInIndex]);
        ++m_nInIndex;
    }
}

void KeyValuesJsonConverter::openObject()
{
    validateInputIndex();

    if ( m_bCreatedObject )
    {
        copyOut(',');
    }

    changeSyntaxSection("begin object", '{');
}

void KeyValuesJsonConverter::closeObject()
{
    changeSyntaxSection("end object", '}');
}

void KeyValuesJsonConverter::openQuotedString()
{
    changeSyntaxSection("begin quoted string", '"');
}

void KeyValuesJsonConverter::closeQuotedString()
{
    changeSyntaxSection("end quoted string", '"');
}

void KeyValuesJsonConverter::changeSyntaxSection(const QString& logName, char delimiter)
{
    validateInputIndex();

    char nextChar[2] = { consumeChar(), '\0' };

    if ( nextChar[0] != delimiter )
    {
        raiseExceptionAtCurrentIndex(QString("Expected '%0' (%1) to %2, but got '%3' (%4).")
                                     .arg(charAsTempString(delimiter))
                                     .arg(static_cast<int>(delimiter))
                                     .arg(logName)
                                     .arg(nextChar)
                                     .arg(static_cast<int>(nextChar[0])));
    }

    copyOut(nextChar, 1);
}
