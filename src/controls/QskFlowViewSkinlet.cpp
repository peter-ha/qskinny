#include "QskFlowViewSkinlet.h"

#include "QskFlowView.h"

#include <QDebug> // ### remove
#include <QSGTransformNode>
#include <QTransform>
#include <QtMath>

QskFlowViewSkinlet::QskFlowViewSkinlet( QskSkin* skin ) : QskSkinlet( skin )
{
    setNodeRoles( { CoversRole } );
}

QskFlowViewSkinlet::~QskFlowViewSkinlet()
{
}

QSGNode* QskFlowViewSkinlet::updateSubNode( const QskSkinnable* skinnable, quint8 /*nodeRole*/, QSGNode* node ) const
{
    if( node == nullptr )
    {
        node = new QSGNode();
    }

    auto flowView = static_cast< const QskFlowView* >( skinnable );

    auto currentIndex = flowView->currentIndex();
    auto count = flowView->visibleCount();
    auto startIndex = currentIndex - count / 2;
    auto startIndexBounded = qMax( startIndex, 0 );
    auto countOffset = startIndexBounded - startIndex;
    auto endIndex = currentIndex + count / 2;
    auto endIndexBounded = qMin( endIndex, flowView->count() - 1 );
    auto padding = 0; // ### style

    auto currentItemWidth = flowView->currentItemWidth();

    // For now, allow only swiping one element at a time (should be changed later):
    auto swipeCompletedFraction = ( flowView->swipeOffset() > currentItemWidth ) ? 1.0 : flowView->swipeOffset() / currentItemWidth;

    // the index of the cover we are currently moving (not the active one); either the one left
    // or right of the active one:
    int movedIndex = -1;

    if( flowView->currentIndex() > 0 && flowView->swipeOffset() > 0 )
    {
        movedIndex = flowView->currentIndex() - 1;
    }
    else if( flowView->currentIndex() < flowView->count() - 1 && flowView->swipeOffset() < 0 )
    {
        movedIndex = flowView->currentIndex() + 1;
    }

    auto movedElementAngle = ( 1 - swipeCompletedFraction ) * flowView->angle();
    auto movedElementRadians = qDegreesToRadians( movedElementAngle );
    auto movedElementSine = qSin( movedElementRadians );
    auto movedElementCosine = qCos( movedElementRadians );
    qreal movedElementScaleFactor = movedElementCosine;
    qreal movedElementWidth = currentItemWidth * movedElementScaleFactor;

    auto nonActiveElementRadians = qDegreesToRadians( flowView->angle() );
    auto nonActiveElementSine = qSin( nonActiveElementRadians );
    auto nonActiveElementCosine = qCos( nonActiveElementRadians );
    qreal nonActiveElementScaleFactor = nonActiveElementCosine;
    qreal nonActiveElementWidth = currentItemWidth * nonActiveElementScaleFactor;

    // ### make off by one nodes invisible
    for( auto a = startIndexBounded; a <= endIndexBounded; ++a )
    {
        auto transformNode = ( node->childCount() > a ) ? static_cast< QSGTransformNode* >( node->childAtIndex( a ) ) : new QSGTransformNode;
        auto oldCoverNode = ( transformNode->childCount() > 0 ) ? transformNode->childAtIndex( 0 ) : nullptr;
        auto coverNode = flowView->nodeAt( a, oldCoverNode );

        auto y = padding;
        qreal shear;
        qreal scale;
        auto x = ( a - startIndexBounded + countOffset ) * movedElementWidth;
        qreal sine, scaleFactor, elementWidth;

        if( a == movedIndex )
        {
            sine = movedElementSine;
            scaleFactor = movedElementScaleFactor;
            elementWidth = movedElementWidth;
        }
        else {
            sine = nonActiveElementSine;
            scaleFactor = nonActiveElementScaleFactor;
            elementWidth = nonActiveElementWidth;
        }

        if( a < currentIndex ) // left of selected node
        {
            shear = -sine;
            scale = scaleFactor;
            y += elementWidth * sine;
        }
        else if( a > currentIndex ) // right of selected node
        {
            x += ( currentItemWidth - elementWidth );
            scale = scaleFactor;
            shear = sine;
        }
        else // selected node
        {
            shear = 0;
            scale = 1;
            y += elementWidth * sine;
        }

        QTransform translateTransform;
        translateTransform.translate( x, y );

        QTransform shearTransform;
        shearTransform.shear( 0, shear );

        QTransform scaleTransform;
        scaleTransform.scale( scale, 1 );

        auto transform = scaleTransform * shearTransform * translateTransform;

        transformNode->setMatrix( { transform } );

        if( transformNode->childCount() == 0 )
        {
            transformNode->appendChildNode( coverNode );
        }

        if( node->childCount() <= a )
        {
            node->appendChildNode( transformNode );
        }
    }

    return node;
}
