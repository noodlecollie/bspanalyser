#ifndef AXIALLYALIGNEDBOUNDINGBOX_H
#define AXIALLYALIGNEDBOUNDINGBOX_H

#include <QVector3D>

class AxiallyAlignedBoundingBox
{
public:
    AxiallyAlignedBoundingBox();
    AxiallyAlignedBoundingBox(const QVector3D& inMin, const QVector3D& inMax);

    QVector3D min() const;
    void setMin(const QVector3D& newMin);

    QVector3D max() const;
    void setMax(const QVector3D& newMax);

private:
    void setMinMax(QVector3D v0, QVector3D v1);

    QVector3D m_vecMin;
    QVector3D m_vecMax;
};

Q_DECLARE_METATYPE(AxiallyAlignedBoundingBox)

#endif // AXIALLYALIGNEDBOUNDINGBOX_H
