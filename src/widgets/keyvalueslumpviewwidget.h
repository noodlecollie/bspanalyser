#ifndef KEYVALUESLUMPVIEWWIDGET_H
#define KEYVALUESLUMPVIEWWIDGET_H

#include <QWidget>

#include "ilumpviewwidget.h"

namespace Ui {
class KeyValuesLumpViewWidget;
}

class KeyValuesLumpViewWidget : public QWidget,
                                public ILumpViewWidget
{
    Q_OBJECT

public:
    explicit KeyValuesLumpViewWidget(QWidget *parent = 0);
    ~KeyValuesLumpViewWidget();

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment) override;

private:
    Ui::KeyValuesLumpViewWidget *ui;
};

#endif // KEYVALUESLUMPVIEWWIDGET_H
