#ifndef HEXDISPLAYWIDGET_H
#define HEXDISPLAYWIDGET_H

#include <QPlainTextEdit>
#include <QSharedPointer>

class HexDisplayWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit HexDisplayWidget(QWidget *parent = nullptr);

    void loadBinaryData(const QByteArray& data);
    void selectBinaryData(int offset, int count);
    int binaryDataLength() const;

signals:

public slots:
};

#endif // HEXDISPLAYWIDGET_H
