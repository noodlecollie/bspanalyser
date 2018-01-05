#ifndef KEYVALUESVIEW_H
#define KEYVALUESVIEW_H

#include <QWidget>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QLoggingCategory>

#include "bsp/bspdatafragment.h"
#include "bsp/bsplumpdef.h"

class KeyValuesView : public QWidget
{
    Q_OBJECT
public:
    explicit KeyValuesView(QWidget *parent = 0);
    ~KeyValuesView();

    void loadLumpData(const QByteArray& data, QString& errorString);

private:
    void initTree();
    void initRaw();
    void initWithGroupBox(const QString& title, QWidget* widget);
    bool loadKeyvaluesDataIntoTree(const QByteArray& kv, QString& outErrorString);
    void processTreeWidgetItem(QTreeWidgetItem* item, const QJsonObject& kvObject);

    QSplitter* m_pSplitter;
    QTreeWidget* m_pTreeView;
    QPlainTextEdit* m_pRawView;
};

#endif // KEYVALUESVIEW_H
