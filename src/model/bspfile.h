#ifndef BSPFILE_H
#define BSPFILE_H

#include <QObject>
#include <QString>
#include <QByteArray>

class BSPFile : public QObject
{
    Q_OBJECT
public:
    BSPFile(QObject* parent = nullptr);

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

#endif // BSPFILE_H
