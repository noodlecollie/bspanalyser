#ifndef BSPDATAFRAGMENT_H
#define BSPDATAFRAGMENT_H

#include <QByteArray>

class BSPDataFragment
{
public:
    BSPDataFragment(const QByteArray& byteArray);
    BSPDataFragment(const QByteArray& byteArray, quint32 inOffset, quint32 inLength);

    const QByteArray& data() const;

    quint32 offset() const;
    void setOffset(quint32 newOffset);

    quint32 length() const;
    void setLength(quint32 newLength);

    const char* rawData() const;

    bool isValid() const;

private:
    void sanitise();

    const QByteArray& m_arrData;
    quint32 m_nOffset;
    quint32 m_nLength;
};

#endif // BSPDATAFRAGMENT_H
