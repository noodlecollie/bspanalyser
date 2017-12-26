#ifndef KEYVALUESJSONCONVERTER_H
#define KEYVALUESJSONCONVERTER_H

#include <QByteArray>

class KeyValuesJsonConverter
{
    friend class EndOfInputException;
public:
    KeyValuesJsonConverter();

    bool convert(const QByteArray& inKV, QByteArray& outJSON, QString& errorString);

private:
    class EndOfInputException;

    enum class ParseState
    {
        OutsideObject = 0,
        InObject,
        InKey,
        BetweenKeyAndValue,
        InValue,
    };

    void convertKeyValuesToJSON();
    void copyOut(const char* data, quint32 dataLength, quint32 offset, quint32 length);
    void copyOut(quint32 offset, quint32 length);
    void copyOut(const char* data, quint32 dataLength);
    void copyOut(char data);

    void initForParsing();
    void raiseExceptionAtCurrentIndex(const QString& message);

    // Does not validate the input index.
    char consumeChar();

    void validateInputIndex();
    bool decideNextActionInObject(ParseState& state);
    void skipWhitespace();
    void skipAllButNonEscapedQuotes();
    void openObject();
    void closeObject();
    void openQuotedString();
    void closeQuotedString();

    void changeSyntaxSection(const QString& logName, char delimiter);

    const QByteArray* m_pIn;
    QByteArray* m_pOut;
    quint32 m_nInIndex;
    quint32 m_nOutIndex;
    ParseState m_nState;

    bool m_bCreatedObject;
    bool m_bCreatedKVPairInObject;
};

#endif // KEYVALUESJSONCONVERTER_H
