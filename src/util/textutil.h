#ifndef TEXTUTIL_H
#define TEXTUTIL_H

#include <QFont>
#include <QByteArray>

namespace TextUtil
{
    QFont monospacedFont(int pointSize);
    QString hexString(const QByteArray& data, quint32 bytesPerBlock = 0);
}

#endif // TEXTUTIL_H
