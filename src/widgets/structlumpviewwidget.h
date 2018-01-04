#ifndef STRUCTLUMPVIEWWIDGET_H
#define STRUCTLUMPVIEWWIDGET_H

#include <QWidget>

#include "ilumpviewwidget.h"

#include "bsp/structlumpdef.h"

namespace Ui {
class StructLumpViewWidget;
}

class StructLumpViewWidget : public QWidget,
                             public ILumpViewWidget
{
    Q_OBJECT

public:
    explicit StructLumpViewWidget(QWidget *parent = 0);
    ~StructLumpViewWidget();

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment) override;

private:
    void initTable();

    Ui::StructLumpViewWidget *ui;
    QSharedPointer<StructLumpDef> m_pStructLumpDef;
};

#endif // STRUCTLUMPVIEWWIDGET_H
