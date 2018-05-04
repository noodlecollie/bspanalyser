#ifndef NOTIMPLEMENTEDPLACEHOLDERWIDGET_H
#define NOTIMPLEMENTEDPLACEHOLDERWIDGET_H

#include <QWidget>

#include "ilumpviewwidget.h"

namespace Ui {
class NotImplementedPlaceholderWidget;
}

class NotImplementedPlaceholderWidget : public QWidget,
                                        public ILumpViewWidget
{
    Q_OBJECT

public:
    explicit NotImplementedPlaceholderWidget(const QString& description = QString(), QWidget *parent = 0);
    ~NotImplementedPlaceholderWidget();

    // ILumpViewWidget
    virtual QWidget* asWidget() override;
    virtual void loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment) override;

private:
    Ui::NotImplementedPlaceholderWidget *ui;
};

#endif // NOTIMPLEMENTEDPLACEHOLDERWIDGET_H
