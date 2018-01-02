#ifndef KEYVALUESLUMPVIEWWIDGET_H
#define KEYVALUESLUMPVIEWWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QLoggingCategory>

#include "ilumpviewwidget.h"

Q_DECLARE_LOGGING_CATEGORY(lcKeyValuesLumpView)

class KeyvaluesLumpViewWidget : public QWidget,
                                public ILumpViewWidget
{
    Q_OBJECT
public:
    explicit KeyvaluesLumpViewWidget(QWidget *parent = 0);
    ~KeyvaluesLumpViewWidget();

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const BSPDataFragment &fragment) override;

private:
    void initTree();
    void initRaw();
    void initWithGroupBox(const QString& title, QWidget* widget);
    bool loadKeyvaluesDataIntoTree(const QByteArray& kv);
    void processTreeWidgetItem(QTreeWidgetItem* item, const QJsonObject& kvObject);

    QSplitter* m_pSplitter;
    QTreeWidget* m_pTreeView;
    QPlainTextEdit* m_pRawView;
};

#endif // KEYVALUESLUMPVIEWWIDGET_H
