#ifndef BSPFILEMODEL_H
#define BSPFILEMODEL_H

#include <QObject>
#include <QString>
#include <QByteArray>

class BSPFileModel : public QObject
{
    Q_OBJECT
public:
    BSPFileModel(QObject* parent = nullptr);

    QString filePath() const;
    const QByteArray& contents() const;
    bool isValid() const;

    bool load(const QString& filePath);
    void clear();

    quint32 version() const;
    quint32 subVersion() const;
    quint64 lumpTableOffset() const;

    bool hasSubVersion() const;
    void setHasSubVersion(bool hasSV);

private:
    QString m_strFilePath;
    QByteArray m_arrData;
    bool m_bHasSubVersion;
};

#endif // BSPFILEMODEL_H
