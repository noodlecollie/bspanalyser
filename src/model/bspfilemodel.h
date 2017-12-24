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

signals:
    void loaded();
    void cleared();

private:
    QString m_strFilePath;
    QByteArray m_arrData;
};

#endif // BSPFILEMODEL_H
