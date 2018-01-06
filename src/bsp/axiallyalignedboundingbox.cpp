#include "axiallyalignedboundingbox.h"

int AxiallyAlignedBoundingBox::m_nMetaTypeId = qRegisterMetaType<AxiallyAlignedBoundingBox>();

AxiallyAlignedBoundingBox::AxiallyAlignedBoundingBox()
    : AxiallyAlignedBoundingBox(QVector3D(), QVector3D())
{
}

AxiallyAlignedBoundingBox::AxiallyAlignedBoundingBox(const QVector3D &inMin, const QVector3D &inMax)
    : m_vecMin(inMin),
      m_vecMax(inMax)
{
}

int AxiallyAlignedBoundingBox::metaTypeId()
{
    return m_nMetaTypeId;
}

QVector3D AxiallyAlignedBoundingBox::min() const
{
    return m_vecMin;
}

void AxiallyAlignedBoundingBox::setMin(const QVector3D &newMin)
{
    setMinMax(newMin, m_vecMax);
}

QVector3D AxiallyAlignedBoundingBox::max() const
{
    return m_vecMax;
}

void AxiallyAlignedBoundingBox::setMax(const QVector3D &newMax)
{
    setMinMax(m_vecMin, newMax);
}

void AxiallyAlignedBoundingBox::setMinMax(QVector3D v0, QVector3D v1)
{
    for ( int index = 0; index < 3; ++index )
    {
        m_vecMin[index] = qMin<float>(v0[index], v1[index]);
        m_vecMax[index] = qMax<float>(v0[index], v1[index]);
    }
}
