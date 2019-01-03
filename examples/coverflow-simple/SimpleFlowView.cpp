#include "SimpleFlowView.h"

#include <QSGSimpleRectNode>

SimpleFlowView::SimpleFlowView( QQuickItem* parent ) : QskFlowView( parent )
{
}

QSGNode* SimpleFlowView::nodeAt( int index, QSGNode* oldNode ) const
{
    auto width = currentItemWidth();

    if( oldNode == nullptr )
    {
        QColor color( 0, 0, index * 50 );
        auto node = new QSGSimpleRectNode( { 0, 0, width, width }, color );
        return node;
    }
    else {
        auto simpleRectNode = static_cast< QSGSimpleRectNode* >( oldNode );
        simpleRectNode->setRect( { 0, 0, width, width } );
        return simpleRectNode;
    }
}
