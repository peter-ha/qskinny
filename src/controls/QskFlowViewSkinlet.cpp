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

    auto flowView = static_cast< const QskFlowView* >( skinnable );

    // ### make those variables const
    auto currentActiveIndex = flowView->currentIndex();
    auto count = flowView->visibleCount();

    auto startIndexUnbounded = currentActiveIndex - count / 2;
    auto startIndex = qMax( startIndexUnbounded, 0 );
    auto leftOffset = startIndex - startIndexUnbounded; // when reaching the beginning of the list

    auto endIndexUnbounded = currentActiveIndex + count / 2;
    auto endIndex = qMin( endIndexUnbounded, flowView->count() - 1 );
    auto rightOffset = endIndexUnbounded - endIndex; // when reaching the end of the list

    auto padding = 0; // ### style

    auto radians = qDegreesToRadians( flowView->angle() );
    auto sine = qSin( radians );
    auto cosine = qCos( radians );
    qreal scaleFactor = cosine;
    auto currentItemWidth = flowView->currentItemWidth();
    qreal rotatedItemWidth = currentItemWidth * scaleFactor;

    // reuse scene graph nodes when swiping by removing and reinserting them:
    auto oldStartIndex = rootNode->leftVisibleIndex();
    auto oldEndIndex = rootNode->rightVisibleIndex();

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

    // Only remove nodes if we have not reached the right number already:
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
        auto x = ( a + leftOffset ) * rotatedItemWidth;

        if( flowViewIndex < currentActiveIndex ) // left of selected node
        {
            shear = -sine;
            scale = scaleFactor;
            y += rotatedItemWidth * sine;
        }
        else if( flowViewIndex > currentActiveIndex ) // right of selected node
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

        if( rootNode->childCount() <= a )
        {
            rootNode->appendChildNode( transformNode );
        }
    }

    rootNode->setVisibleIndexes( startIndex, endIndex );

    return rootNode;
}
