#include "hexdisplaywidget.h"

namespace
{
    static constexpr char HEX_CHARS[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    static constexpr int BYTES_PER_SPACE = 4;
}

HexDisplayWidget::HexDisplayWidget(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setLineWrapMode(QPlainTextEdit::WidgetWidth);
    setPlaceholderText(tr("No file loaded."));
    setReadOnly(true);

    QFont font("monospace", 10);
    font.setStyleHint(QFont::Monospace);
    setFont(font);
}

void HexDisplayWidget::setBSPFile(BSPFile *file)
{
    m_pBSPFile = file;
}

void HexDisplayWidget::selectBinaryData(quint32 offset, quint32 count)
{
    if ( !m_pBSPFile )
    {
        return;
    }

    quint32 dataLength = m_pBSPFile->contents().length();

    if ( offset < 0 )
    {
        offset = 0;
    }
    else if ( offset > dataLength )
    {
        offset = dataLength;
    }

    quint32 endPos = offset + count;
    if ( endPos > dataLength )
    {
        endPos = dataLength;
    }

    QTextCursor newCursor;
    newCursor.setPosition(byteIndexToTextIndex(offset), QTextCursor::MoveAnchor);
    newCursor.setPosition(byteIndexToTextIndex(endPos), QTextCursor::KeepAnchor);

    setTextCursor(newCursor);
}

void HexDisplayWidget::loadBSPData()
{
    if ( !m_pBSPFile )
    {
        return;
    }

    int bspLength = m_pBSPFile->contents().length();
    quint32 indexOfLastByte = byteIndexToTextIndex(bspLength - 1);

    QString textContents;

    // +2 since each byte gets 2 characters.
    textContents.resize(indexOfLastByte + 2, ' ');

    for ( int index = 0; index < bspLength; ++index )
    {
        char byte = m_pBSPFile->contents().at(index);
        quint32 textIndex = byteIndexToTextIndex(index);

        textContents[textIndex] = HEX_CHARS[(byte & 0xF0) >> 4];
        textContents[textIndex + 1] = HEX_CHARS[byte & 0x0F];
    }

    setPlainText(textContents);
}

quint32 HexDisplayWidget::byteIndexToTextIndex(quint32 byteIndex)
{
    // The following rules apply:
    // - 2 text chars per byte
    // - One blank space every BYTES_PER_SPACE bytes

    int totalSpaces = byteIndex / BYTES_PER_SPACE;
    return (2 * byteIndex) + totalSpaces;
}
