#ifndef STRUCTLUMPVIEWWIDGET_H
#define STRUCTLUMPVIEWWIDGET_H

#include <QWidget>
#include <QLoggingCategory>

#include "ilumpviewwidget.h"

#include "bsp/structlumpdef.h"

Q_DECLARE_LOGGING_CATEGORY(lcStructLumpViewWidget)

namespace Ui {
class StructLumpViewWidget;
}

class StructLumpViewWidget : public QWidget,
                             public ILumpViewWidget
{
    Q_OBJECT

public:
    explicit StructLumpViewWidget(QWidget *parent = Q_NULLPTR);
    ~StructLumpViewWidget() override;

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment) override;

private slots:
    void lumpItemChanged(int item);

private:
    void initTable();
    void setTableMemberDefinitions();
    void updateLumpItemCount();
    void updateUI();
    QByteArray getStructData(int item) const;
    void setItem(int row, int column, const QString& data);

    Ui::StructLumpViewWidget *ui;
    QSharedPointer<StructLumpDef> m_pStructLumpDef;
    QByteArray m_LumpData;
    quint32 m_nItemCount;
};

#endif // STRUCTLUMPVIEWWIDGET_H
