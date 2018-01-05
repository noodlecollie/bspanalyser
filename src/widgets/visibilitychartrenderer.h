#ifndef VISIBILITYCHARTRENDERER_H
#define VISIBILITYCHARTRENDERER_H

#include <QGraphicsScene>
#include <QPen>
#include <QVector2D>

class VisibilityChartRenderer
{
public:
    VisibilityChartRenderer(QGraphicsScene& scene);

    void drawDefaultAxes();

private:
    inline static QVector2D leafToScene(const QVector2D& coord)
    {
        return QVector2D(coord.x() * 10, coord.y() * -10);
    }

    static QPen createAxisPen();

    QGraphicsScene& m_Scene;
};

#endif // VISIBILITYCHARTRENDERER_H
