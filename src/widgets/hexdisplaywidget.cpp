#include "hexdisplaywidget.h"

namespace
{
    static const char HEX_CHARS[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
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

void HexDisplayWidget::loadBinaryData(const QByteArray &data)
{
    clear();

    QString contents;
    contents.resize(data.length() * 2, '0');

    for ( int index = 0; index < data.length(); ++index )
    {
        contents[2 * index] = HEX_CHARS[(data[index] & 0xF0) >> 4];
        contents[(2 * index) + 1] = HEX_CHARS[data[index] & 0x0F];
    }

    setPlainText(contents);
}

void HexDisplayWidget::selectBinaryData(int offset, int count)
{
    int dataLength = binaryDataLength();

    if ( offset < 0 )
    {
        offset = 0;
    }
    else if ( offset > dataLength )
    {
        offset = dataLength;
    }

    int endPos = offset + count;
    if ( endPos > dataLength )
    {
        endPos = dataLength;
    }

    QTextCursor newCursor;
    newCursor.setPosition(offset, QTextCursor::MoveAnchor);
    newCursor.setPosition(endPos, QTextCursor::KeepAnchor);

    setTextCursor(newCursor);
}

int HexDisplayWidget::binaryDataLength() const
{
    // 2 text chars per byte of data.
    return toPlainText().length() / 2;
}
