#ifndef VISCOMPRESSOR_H
#define VISCOMPRESSOR_H

#include <QByteArray>

class VisCompressor
{
public:
    VisCompressor();

    void compress(const QByteArray& inUncompressed, QByteArray& outCompressed);
    void decompress(const QByteArray& inCompressed, QByteArray& outUncompressed);

    static quint32 bytesRequiredPerCompressedRow(quint32 numLeaves);
    static quint32 alignedBytesRequiredPerCompressedRow(quint32 numLeaves);
};

#endif // VISCOMPRESSOR_H
