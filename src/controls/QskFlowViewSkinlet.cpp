#include "QskFlowViewSkinlet.h"

#include "QskFlowView.h"

#include <QDebug> // ### remove
#include <QSGTransformNode>
#include <QTransform>
#include <QtMath>


class QskFlowViewNode : public QSGNode
{
public:
    QskFlowViewNode() : QSGNode()
    {
    }

    void setVisibleIndexes( int left, int right )
    {
        m_left = left;
        m_right = right;
    }

    int leftVisibleIndex() const
    {
        return m_left;
    }

    int rightVisibleIndex() const
    {
        return m_right;
    }

private:
    int m_left = -1;
    int m_right = -1;
};


QskFlowViewSkinlet::QskFlowViewSkinlet( QskSkin* skin ) : QskSkinlet( skin )
{
    setNodeRoles( { CoversRole } );
}

QskFlowViewSkinlet::~QskFlowViewSkinlet()
{
}

QSGNode* QskFlowViewSkinlet::updateSubNode( const QskSkinnable* skinnable, quint8 /*nodeRole*/, QSGNode* node ) const
{
    auto flowViewNode = static_cast< QskFlowViewNode* >( node );

    if( flowViewNode == nullptr )
    {
        flowViewNode = new QskFlowViewNode;
    }

    auto flowView = static_cast< const QskFlowView* >( skinnable );

    // ### make those variables const
    auto currentIndex = flowView->currentIndex();
    auto count = flowView->visibleCount();
    auto startIndexUnbounded = currentIndex - count / 2;
    auto startIndex = qMax( startIndexUnbounded, 0 );
    auto countOffset = startIndex - startIndexUnbounded;
    auto endIndexUnbounded = currentIndex + count / 2;
    auto endIndex = qMin( endIndexUnbounded, flowView->count() - 1 );
    auto padding = 0; // ### style

    auto radians = qDegreesToRadians( flowView->angle() );
    auto sine = qSin( radians );
    auto cosine = qCos( radians );
    qreal scaleFactor = cosine;
    auto currentItemWidth = flowView->currentItemWidth();
    qreal rotatedItemWidth = currentItemWidth * scaleFactor;

    // reuse scene graph nodes when swiping by removing and reinserting them:
    auto oldStartIndex = flowViewNode->leftVisibleIndex();
    auto oldEndIndex = flowViewNode->rightVisibleIndex();

    if( oldStartIndex > -1 && oldStartIndex < startIndex )
    {
        for( int a = oldStartIndex; a < startIndex; ++a )
        {
            qDebug() << "reinsert node" << a << "at the end";
        }
    }

    if( oldEndIndex > -1 && oldEndIndex > endIndex )
    {
        for( int a = endIndex; a < oldEndIndex; ++a )
        {
            qDebug() << "reinsert node" << a << "at the front";
        }
    }

    if( flowView->swipeDirection() == Qsk::RightToLeft )
    {
//        qDebug() << "rtl" << startIndex << oldStartIndex;
    }
    else if( flowView->swipeDirection() == Qsk::LeftToRight )
    {
//        qDebug() << "ltr" << startIndex << oldStartIndex;
    }

    // layout visible nodes:
    for( auto a = startIndex; a <= endIndex; ++a )
    {
        auto transformNode = ( flowViewNode->childCount() > a ) ? static_cast< QSGTransformNode* >( flowViewNode->childAtIndex( a ) ) : new QSGTransformNode;
        auto oldCoverNode = ( transformNode->childCount() > 0 ) ? transformNode->childAtIndex( 0 ) : nullptr;
        auto coverNode = flowView->nodeAt( a, oldCoverNode );

        auto y = padding;
        qreal shear;
        qreal scale;
        auto x = ( a - startIndex + countOffset ) * rotatedItemWidth;

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

        if( flowViewNode->childCount() <= a )
        {
            flowViewNode->appendChildNode( transformNode );
        }
    }

    flowViewNode->setVisibleIndexes( startIndex, endIndex );

    return flowViewNode;
}
