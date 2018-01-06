#ifndef AXIALLYALIGNEDBOUNDINGBOX_H
#define AXIALLYALIGNEDBOUNDINGBOX_H

#include <QVector3D>
#include <QMetaType>

class AxiallyAlignedBoundingBox
{
public:
    AxiallyAlignedBoundingBox();
    AxiallyAlignedBoundingBox(const QVector3D& inMin, const QVector3D& inMax);

    static int metaTypeId();

    QVector3D min() const;
    void setMin(const QVector3D& newMin);

    QVector3D max() const;
    void setMax(const QVector3D& newMax);

private:
    void setMinMax(QVector3D v0, QVector3D v1);

    static int m_nMetaTypeId;

    QVector3D m_vecMin;
    QVector3D m_vecMax;
};

Q_DECLARE_METATYPE(AxiallyAlignedBoundingBox)

#endif // AXIALLYALIGNEDBOUNDINGBOX_H
