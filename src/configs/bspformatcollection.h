#ifndef BSPFORMATCOLLECTION_H
#define BSPFORMATCOLLECTION_H

#include <QLoggingCategory>
#include <QHash>
#include <QByteArray>
#include <QSharedPointer>

Q_DECLARE_LOGGING_CATEGORY(lcBSPFormatCollection)

class BSPFormatCollection
{
public:
    BSPFormatCollection();

    void initialise();

private:
    void loadFormat(const QString& filePath);

    QHash<quint32, QSharedPointer<QByteArray>> m_hshFormatFiles;
};

#endif // BSPFORMATCOLLECTION_H
