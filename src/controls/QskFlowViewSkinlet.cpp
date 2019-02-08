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
    auto rootNode = static_cast< QskFlowViewNode* >( node );

    if( rootNode == nullptr )
    {
        rootNode = new QskFlowViewNode;
    }

    const auto flowView = static_cast< const QskFlowView* >( skinnable );

    auto swipeFraction = flowView->swipeOffset() / flowView->currentItemWidth();
    // for now, only support swiping one element at a time (### allow fast swipes)
    swipeFraction = qMin( swipeFraction, 1.0 );
    swipeFraction = qMax( swipeFraction, -1.0 );

    const auto currentActiveIndex = flowView->currentIndex();

    int swipedToIndex = -1;

    if( flowView->swipeOffset() < 0 && currentActiveIndex > 0 )
    {
        swipedToIndex = currentActiveIndex - 1;
    }
    else if( flowView->swipeOffset() > 0 && currentActiveIndex < flowView->count() - 1 )
    {
        swipedToIndex = currentActiveIndex + 1;
    }

    const auto count = flowView->visibleCount();

    const auto startIndexUnbounded = currentActiveIndex - count / 2;
    const auto startIndex = qMax( startIndexUnbounded, 0 );
    const auto leftOffset = startIndex - startIndexUnbounded; // when reaching the beginning of the list

    const auto endIndexUnbounded = currentActiveIndex + count / 2;
    const auto endIndex = qMin( endIndexUnbounded, flowView->count() - 1 );
    const auto rightOffset = endIndexUnbounded - endIndex; // when reaching the end of the list

    const auto padding = 0; // ### style

    const auto radians = qDegreesToRadians( flowView->angle() );
    const auto sine = qSin( radians );
    const auto cosine = qCos( radians );
    const qreal scaleFactor = cosine;
    const qreal rotatedItemWidth = flowView->currentItemWidth() * scaleFactor;

    const auto currentItemScaleFactor = ( 1 - qAbs( swipeFraction ) ) + qAbs( swipeFraction ) * scaleFactor;
    const auto currentItemWidth = flowView->currentItemWidth() * currentItemScaleFactor;
    const auto nextItemScaleFactor = qAbs( swipeFraction ) + ( 1 - qAbs( swipeFraction ) ) * scaleFactor;
    const auto nextItemWidth = flowView->currentItemWidth() * nextItemScaleFactor;

    // reuse scene graph nodes when swiping by removing and reinserting them:
    const auto oldStartIndex = rootNode->leftVisibleIndex();
    const auto oldEndIndex = rootNode->rightVisibleIndex();

    if( oldStartIndex > -1 )
    {
        // scrolling to the left:

        for( int a = 0; a < startIndex - oldStartIndex; ++a )
        {
            auto childNode = rootNode->firstChild();
            rootNode->removeChildNode( childNode );
            rootNode->appendChildNode( childNode );
        }
    }

    if( oldEndIndex > -1 )
    {
        // scrolling to the right:

        for( int a = 0; a < oldEndIndex - endIndex; ++a )
        {
            auto childNode = rootNode->lastChild();
            rootNode->removeChildNode( childNode );
            rootNode->prependChildNode( childNode );
        }
    }


    // if at the beginning or the end of the list, we might have to remove some nodes:

    // Only remove nodes if we have not reached the right number of scene graph nodes already,
    // otherwise we would be removing here and later inserting nodes upon every swipe even if nothing changes:

    if( flowView->visibleCount() - rootNode->childCount() < leftOffset )
    {
        for( int a = 0; a < leftOffset; ++a )
        {
            auto childNode = rootNode->firstChild();
            rootNode->removeChildNode( childNode );
        }
    }

    if( flowView->visibleCount() - rootNode->childCount() < rightOffset )
    {
        for( int a = 0; a < rightOffset; ++a )
        {
            auto childNode = rootNode->lastChild();
            rootNode->removeChildNode( childNode );
        }
    }


    // layout visible nodes:

    for( auto a = 0; a <= endIndex - startIndex; ++a )
    {
        const auto flowViewIndex = startIndex + a;

        auto transformNode = ( rootNode->childCount() > a ) ? static_cast< QSGTransformNode* >( rootNode->childAtIndex( a ) ) : new QSGTransformNode;
        auto oldCoverNode = ( transformNode->childCount() > 0 ) ? transformNode->childAtIndex( 0 ) : nullptr;
        auto coverNode = flowView->nodeAt( flowViewIndex, oldCoverNode );

        auto y = padding;
        qreal shear;
        qreal scale;
        auto x = ( a + leftOffset + swipeFraction ) * rotatedItemWidth;

        if( flowViewIndex == swipedToIndex )
        {
            if( swipeFraction < 0 )
            {
                shear = ( -1 - swipeFraction ) * sine;
                scale = nextItemScaleFactor;
                y += rotatedItemWidth * sine;
            }
            else
            {
                shear = ( 1 - swipeFraction ) * sine;
                scale = nextItemScaleFactor;
                x += currentItemWidth - rotatedItemWidth;
                y += swipeFraction * rotatedItemWidth * sine;
            }
        }
        else if( flowViewIndex < currentActiveIndex ) // left of selected node
        {
            shear = -sine;
            scale = scaleFactor;
            y += rotatedItemWidth * sine;
        }
        else if( flowViewIndex > currentActiveIndex ) // right of selected node
        {
            x += ( currentItemWidth - rotatedItemWidth ) + ( nextItemWidth - rotatedItemWidth );
            shear = sine;
            scale = scaleFactor;
        }
        else // selected node
        {
            shear = -1 * swipeFraction * sine;
            scale = currentItemScaleFactor;

            if( swipeFraction > 0 )
            {
                y += rotatedItemWidth * sine;
            }
            else
            {
                x += nextItemWidth - rotatedItemWidth;
                y += ( 1 + swipeFraction ) * rotatedItemWidth * sine;
            }
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

        if( rootNode->childCount() <= a )
        {
            rootNode->appendChildNode( transformNode );
        }

    }

    rootNode->setVisibleIndexes( startIndex, endIndex );

    return rootNode;
}
