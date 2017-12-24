#ifndef HEXDISPLAYWIDGET_H
#define HEXDISPLAYWIDGET_H

#include <QPlainTextEdit>
#include <QSharedPointer>

#include "model/bspfile.h"

class HexDisplayWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit HexDisplayWidget(QWidget *parent = nullptr);

    void setBSPFile(BSPFile* file);
    void loadBSPData();

    void selectBinaryData(quint32 offset, quint32 count);

signals:

public slots:

private:
    static quint32 byteIndexToTextIndex(quint32 byteIndex);

    BSPFile* m_pBSPFile;
};

#endif // HEXDISPLAYWIDGET_H
