#ifndef VISIBILITYLUMPVIEWWIDGET_H
#define VISIBILITYLUMPVIEWWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QScopedPointer>

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

protected:
    virtual void showEvent(QShowEvent *event) override;

private:
    void setLumpDef(const QSharedPointer<BSPLumpDef>& lumpDef);
    void initInformationArea();
    void updateInformationArea();
    void updateLabels();
    void updateNotesBox();
    void calculateNumberOfLeaves();
    void initGraphicsScene();
    QGraphicsScene* createEmptyVisChart();

    Ui::VisibilityLumpViewWidget *ui;
    QTextEdit* m_pNotesBox;

    QSharedPointer<VisibilityLumpDef> m_pLumpDef;
    quint32 m_nLeafCount;
    QVector<QString> m_liNotes;
    QScopedPointer<QGraphicsScene> m_pGraphicsScene;
    bool m_bFitSceneInView;
};

#endif // VISIBILITYLUMPVIEWWIDGET_H
