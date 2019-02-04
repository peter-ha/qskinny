#include "SimpleFlowView.h"

#include <QSGSimpleRectNode>

SimpleFlowView::SimpleFlowView( QQuickItem* parent ) : QskFlowView( parent )
{
}

QSGNode* SimpleFlowView::nodeAt( int index, QSGNode* oldNode ) const
{
    const auto width = currentItemWidth();
    const qreal fraction = qreal( index ) / count();
    const auto color = QColor::fromHslF( fraction, 0.95, 0.5 );
    const QRectF rect( 0, 0, width, width );

    if( oldNode == nullptr )
    {
        auto node = new QSGSimpleRectNode( rect, color );
        return node;
    }
    else {
        auto simpleRectNode = static_cast< QSGSimpleRectNode* >( oldNode );

        if( simpleRectNode->rect() != rect )
        {
            simpleRectNode->setRect( rect );
        }

        if( simpleRectNode->color() != color )
        {
            simpleRectNode->setColor( color );
        }

        return simpleRectNode;
    }
}
