#include "viscompressor.h"

VisCompressor::VisCompressor()
{

}

void VisCompressor::compress(const QByteArray &inUncompressed, QByteArray &outCompressed)
{
    outCompressed.clear();

    if ( inUncompressed.count() < 1 )
    {
        return;
    }

    for ( int inIndex = 0; inIndex < inUncompressed.count(); ++inIndex )
    {
        char inValue = inUncompressed[inIndex];
        outCompressed.append(inValue);

        if ( inValue != 0)
        {
            continue;
        }

        // The byte was zero. RLE the run of zeroes.
        unsigned char run = 1;
        for ( ; run < 255 && inIndex + run < inUncompressed.count(); ++run )
        {
            if ( inUncompressed[inIndex + run] )
            {
                break;
            }
        }

        outCompressed.append(static_cast<char>(run));
        inIndex += run;
    }
}

void VisCompressor::decompress(const QByteArray &inCompressed, QByteArray &outUncompressed)
{
    outUncompressed.clear();

    if ( inCompressed.count() < 1 )
    {
        return;
    }

    for ( int inIndex = 0; inIndex < inCompressed.count(); ++inIndex )
    {
        char inByte = inCompressed[inIndex];

        if ( inByte != 0 )
        {
            outUncompressed.append(inByte);
            continue;
        }

        // When a zero is encountered, the next byte specifies the length of the run.
        unsigned char run = 1;

        if ( inIndex < inCompressed.count() - 1 )
        {
            run = static_cast<unsigned char>(inCompressed[++inIndex]);
        }

        outUncompressed.append(run, 0);
    }
}

quint32 VisCompressor::bytesRequiredPerCompressedRow(quint32 numLeaves)
{
    return (numLeaves + 7) / 8;
}

quint32 VisCompressor::alignedBytesRequiredPerCompressedRow(quint32 numLeaves)
{
    size_t unalignedBytes = bytesRequiredPerCompressedRow(numLeaves);
    size_t remainder = unalignedBytes % 4;

    return remainder ? unalignedBytes + (4 - remainder) : unalignedBytes;
}
