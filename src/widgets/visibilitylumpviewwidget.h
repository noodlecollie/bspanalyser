#ifndef VISIBILITYLUMPVIEWWIDGET_H
#define VISIBILITYLUMPVIEWWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include "widgets/ilumpviewwidget.h"
#include "bsp/visibilitylumpdef.h"

namespace Ui {
class VisibilityLumpViewWidget;
}

class VisibilityLumpViewWidget : public QWidget,
                                 public ILumpViewWidget
{
    Q_OBJECT

public:
    explicit VisibilityLumpViewWidget(QWidget *parent = 0);
    ~VisibilityLumpViewWidget();

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef>& lumpDef, const BSPDataFragment &fragment) override;

private:
    void setLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef);
    void updateLabels();
    quint32 calculateNumberOfLeaves();

    Ui::VisibilityLumpViewWidget *ui;
    QSharedPointer<VisibilityLumpDef> m_pLumpDef;
};

#endif // VISIBILITYLUMPVIEWWIDGET_H
