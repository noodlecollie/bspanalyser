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
    QSharedPointer<QByteArray> format(quint32 version) const;
    QString sourceFileName(quint32 version) const;

private:
    void loadFormat(const QString& filePath);

    QHash<quint32, QSharedPointer<QByteArray>> m_hshFormatFiles;
    QHash<quint32, QString> m_hshFormatFileNames;
};

#endif // BSPFORMATCOLLECTION_H
