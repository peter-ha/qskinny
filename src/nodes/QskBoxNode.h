/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_BOX_NODE_H
#define QSK_BOX_NODE_H

#include "QskGlobal.h"

class QskBoxShapeMetrics;
class QskBoxBorderMetrics;
class QskBoxBorderColors;
class QskGradient;
class QRectF;

#include <QSGNode>

class QSK_EXPORT QskBoxNode : public QSGGeometryNode
{
public:
    QskBoxNode();
    virtual ~QskBoxNode();

    void setBoxData( const QRectF& rect, 
        const QskBoxShapeMetrics&, const QskBoxBorderMetrics&,
        const QskBoxBorderColors&, const QskGradient& );

    void setBoxData( const QRectF& rect, const QskGradient& );

private:
    void setMonochrome( bool on );

    uint m_metricsHash;
    uint m_colorsHash;
    QRectF m_rect;

    QSGGeometry m_geometry;
};

#endif
