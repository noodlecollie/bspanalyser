#include "bspdatafragment.h"

BSPDataFragment::BSPDataFragment(const QByteArray& byteArray)
    : BSPDataFragment(byteArray, 0, 0)
{

}

BSPDataFragment::BSPDataFragment(const QByteArray& byteArray, quint32 inOffset, quint32 inLength)
    : m_arrData(byteArray),
      m_nOffset(inOffset),
      m_nLength(inLength)
{
    sanitise();
}

const QByteArray& BSPDataFragment::data() const
{
    return m_arrData;
}

quint32 BSPDataFragment::offset() const
{
    return m_nOffset;
}

void BSPDataFragment::setOffset(quint32 newOffset)
{
    m_nOffset = newOffset;
    sanitise();
}

quint32 BSPDataFragment::length() const
{
    return m_nLength;
}

void BSPDataFragment::setLength(quint32 newLength)
{
    m_nLength = newLength;
    sanitise();
}

const char* BSPDataFragment::rawData() const
{
    return m_arrData.constData() + m_nOffset;
}

bool BSPDataFragment::isValid() const
{
    return m_nLength > 0;
}

void BSPDataFragment::sanitise()
{
    quint32 dataLength = m_arrData.length();

    if ( m_nOffset >= dataLength )
    {
        m_nOffset = dataLength;
    }

    if ( m_nOffset + m_nLength > dataLength )
    {
        m_nLength = dataLength - m_nOffset;
    }
}
