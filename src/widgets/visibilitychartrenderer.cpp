#include "visibilitychartrenderer.h"

VisibilityChartRenderer::VisibilityChartRenderer(QGraphicsScene &scene)
    : m_Scene(scene)
{
}

void VisibilityChartRenderer::drawDefaultAxes()
{
    QPen pen = createAxisPen();

    QVector2D xMin = leafToScene(QVector2D(-1, 0));
    QVector2D xMax = leafToScene(QVector2D(10, 0));
    QVector2D yMin = leafToScene(QVector2D(0, -1));
    QVector2D yMax = leafToScene(QVector2D(0, 10));

    m_Scene.clear();
    m_Scene.addLine(xMin.x(), xMin.y(), xMax.x(), xMax.y(), pen);
    m_Scene.addLine(yMin.x(), yMin.y(), yMax.x(), yMax.y(), pen);
    m_Scene.setSceneRect(m_Scene.itemsBoundingRect());
}

QPen VisibilityChartRenderer::createAxisPen()
{
    QPen pen(Qt::black);
    pen.setWidth(1);
    return pen;
}
