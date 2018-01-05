#ifndef VISIBILITYCHARTVIEW_H
#define VISIBILITYCHARTVIEW_H

#include <QGraphicsView>

class VisibilityChartView : public QGraphicsView
{
public:
    VisibilityChartView(QWidget* parent = nullptr);

    void fillView(const QRectF& rect, Qt::AspectRatioMode mode = Qt::IgnoreAspectRatio);
};

#endif // VISIBILITYCHARTVIEW_H
