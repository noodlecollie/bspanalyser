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

    bool hasFormat(quint32 version) const;
    QSharedPointer<QByteArray> format(const QByteArray& fileData) const;
    QString sourceFileName(quint32 version) const;

private:
    void loadFormat(const QString& filePath);

    QHash<quint64, QSharedPointer<QByteArray>> m_hshFormatFiles;
    QHash<quint64, QString> m_hshFormatFileNames;
    QHash<quint32, bool> m_hshVersionHasSubVersions;
};

#endif // BSPFORMATCOLLECTION_H
