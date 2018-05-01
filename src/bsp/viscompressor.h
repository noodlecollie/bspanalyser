#ifndef VISCOMPRESSOR_H
#define VISCOMPRESSOR_H

#include <QByteArray>

class VisCompressor
{
public:
    VisCompressor();

    void compress(const QByteArray& inUncompressed, QByteArray& outCompressed);
    void decompress(const QByteArray& inCompressed, QByteArray& outUncompressed);
    QByteArray uncompressedRow(const QByteArray& uncompressedData, quint32 numLeaves, quint32 row);

    static quint32 bytesRequiredPerUncompressedRow(quint32 numLeaves);
    static quint32 alignedBytesRequiredPerUncompressedRow(quint32 numLeaves);
};

#endif // VISCOMPRESSOR_H
