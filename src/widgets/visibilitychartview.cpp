#include "visibilitychartview.h"

#include <QtDebug>

VisibilityChartView::VisibilityChartView(QWidget *parent)
    : QGraphicsView(parent)
{

}

void VisibilityChartView::fillView(const QRectF &rect, Qt::AspectRatioMode mode)
{
    fitInView(rect, mode);

    QRectF viewRect = mapFromScene(rect).boundingRect();
    qreal xScale = static_cast<qreal>(width()) / viewRect.width();
    qreal yScale = static_cast<qreal>(height()) / viewRect.height();
    qDebug() << xScale << yScale;

    switch ( mode )
    {
        case Qt::KeepAspectRatio:
        {
            qreal minScale = qMin(xScale, yScale);
            scale(minScale, minScale);
            break;
        }

        case Qt::KeepAspectRatioByExpanding:
        {
            qreal maxScale = qMax(xScale, yScale);
            scale(maxScale, maxScale);
            break;
        }

        default:
        {
            scale(xScale, yScale);
            break;
        }
    }
}
