#include "QskFlowView.h"

#include <QtMath>

QskFlowView::QskFlowView( QQuickItem* parent ) : QskControl( parent ),
    m_angle( 30 ), // ### there is something wrong with the angles (try e.g. 80 degrees)
    m_visibleCount( 5 ),
    m_currentIndex( -1 )
{

}

QskFlowView::~QskFlowView()
{
}

qreal QskFlowView::angle() const
{
    return m_angle;
}

void QskFlowView::setAngle( qreal angle )
{
    m_angle = angle;
}

int QskFlowView::visibleCount() const
{
    // should be an odd number
    return m_visibleCount;
}

void QskFlowView::setVisibleCount( int count )
{
    m_visibleCount = count;
}

int QskFlowView::currentIndex() const
{
    return m_currentIndex;
}

void QskFlowView::setCurrentIndex( int index )
{
    m_currentIndex = index;
}

qreal QskFlowView::currentItemWidth() const
{
    auto radians = qDegreesToRadians( angle() );
    qreal scaleFactor = qCos( radians ); // ### does not seem to be quite right yet for ~ 45 degrees
    auto width = contentsRect().width() / ( 1 + ( visibleCount() - 1 ) * scaleFactor );

    return width;
}
