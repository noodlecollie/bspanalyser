#include "textutil.h"

namespace TextUtil
{
    static constexpr char HEX_CHARS[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    QFont monospacedFont(int pointSize)
    {
        QFont font("Courier", pointSize);
        font.setStyleHint(QFont::Monospace);
        return font;
    }

    QString hexString(const QByteArray& data, quint32 bytesPerBlock)
    {
        QString out;

        // This is rough, but it doesn't need to be 100% precise.
        int reserveSize = data.length() * 2;
        if ( bytesPerBlock > 0 )
        {
            reserveSize += data.length() / bytesPerBlock;
        }

        out.reserve(reserveSize);

        for ( qint32 index = 0; index < data.length(); ++index )
        {
            if ( index > 0 && bytesPerBlock > 0 && index % bytesPerBlock == 0 )
            {
                out.append(' ');
            }

            unsigned char ch = static_cast<unsigned char>(data.at(index));
            out.append(HEX_CHARS[(ch & 0xF0) >> 4]);
            out.append(HEX_CHARS[ch & 0x0F]);
        }

        return out;
    }
}
