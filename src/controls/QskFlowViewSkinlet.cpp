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

    auto radians = qDegreesToRadians( flowView->angle() );
    auto sine = qSin( radians );
    auto cosine = qCos( radians );
    qreal scaleFactor = cosine;
    auto currentItemWidth = flowView->currentItemWidth();
    qreal rotatedItemWidth = currentItemWidth * scaleFactor;

    // ### make off by one nodes invisible
    for( auto a = startIndexBounded; a <= endIndexBounded; ++a )
    {
        auto transformNode = ( node->childCount() > a ) ? static_cast< QSGTransformNode* >( node->childAtIndex( a ) ) : new QSGTransformNode;
        auto oldCoverNode = ( transformNode->childCount() > 0 ) ? transformNode->childAtIndex( 0 ) : nullptr;
        auto coverNode = flowView->nodeAt( a, oldCoverNode );

        auto y = padding;
        qreal shear;
        qreal scale;
        auto x = ( a - startIndexBounded + countOffset ) * rotatedItemWidth;

        if( a < currentIndex ) // left of selected node
        {
            shear = -sine;
            scale = scaleFactor;
            y += rotatedItemWidth * sine;
        }
        else if( a > currentIndex ) // right of selected node
        {
            x += ( currentItemWidth - rotatedItemWidth );
            scale = scaleFactor;
            shear = sine;
        }
        else // selected node
        {
            shear = 0;
            scale = 1;
            y += rotatedItemWidth * sine;
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
