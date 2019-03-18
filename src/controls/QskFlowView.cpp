// ### add proper licenses everywhere

#include "QskFlowView.h"

#include "QskEvent.h"
#include "QskFlickAnimator.h"
#include "QskGesture.h"

#include <QtMath>

QSK_SUBCONTROL( QskFlowView, Panel )

namespace
{
    // ### copied from QskScrollView, need to unify those
    class FlickAnimator final : public QskFlickAnimator
    {
      public:
        FlickAnimator()
        {
            // skin hints: TODO
            setDuration( 1000 );
            setEasingCurve( QEasingCurve::OutCubic );
        }

        void setFlowView( QskFlowView* flowView )
        {
            m_flowView = flowView;
        }

        void translate( qreal dx, qreal /*dy*/ ) override
        {
            const auto pos = m_flowView->swipeOffset();
            const auto newOffset = pos + dx;

            const auto nodesSwipeOffset = m_flowView->swipeOffset() / m_flowView->currentItemWidth();
            const auto velocity = animatedVelocity();

            // When coming to an end of a swipe, we need to align to an element
            // i.e. not stop the animation in the middle:

            // ### weird issue when swiping during another swipe (probably a swipe is started the values are reset)
            if( velocity < 750.0 )
            {
                // The heuristics here can be tuned, or the "bounce back" effect could also be turned off
                auto newIndex = qRound( m_flowView->oldIndex() - nodesSwipeOffset );
                qDebug() << "new index:" << newIndex << "old index:" << m_flowView->oldIndex() << pos;

                const auto targetSwipePosition = ( m_flowView->oldIndex() - newIndex ) * m_flowView->currentItemWidth();
                const auto fractionLeftToSwipe = targetSwipePosition - m_flowView->swipeOffset();
                const auto swipeAdjust = ( qFuzzyIsNull( velocity ) ) ? fractionLeftToSwipe : fractionLeftToSwipe / 5;
                qDebug() << "swipe adjust:" << swipeAdjust;

                m_flowView->setSwipeOffset( newOffset + swipeAdjust );
            }
            else
            {
                m_flowView->setSwipeOffset( newOffset );
            }

        }

        void done() override
        {
            m_flowView->adjustIndexAndSwipeOffset();
        }

      private:
        QskFlowView* m_flowView;
    };
}

class QskFlowView::PrivateData
{
  public:
    PrivateData()
    {
    }

    qreal angle = 40;
    int visibleCount = 5;
    int currentIndex = -1;
    int oldIndex = -1;
    int count = 0;

    double swipeOffset = 0.0;
    QskPanGestureRecognizer panRecognizer;
    FlickAnimator flicker;
};


QskFlowView::QskFlowView( QQuickItem* parent )
    : QskControl( parent ),
    m_data( new PrivateData )
{
    m_data->flicker.setFlowView( this );

    m_data->panRecognizer.setOrientations( Qt::Horizontal );
    m_data->panRecognizer.setWatchedItem( this );

    setAcceptedMouseButtons( Qt::LeftButton ); // to get gesture events from the mouse as well
}

QskFlowView::~QskFlowView()
{
}

qreal QskFlowView::angle() const
{
    return m_data->angle;
}

void QskFlowView::setAngle( qreal angle )
{
    m_data->angle = angle;
}

int QskFlowView::visibleCount() const
{
    // should be an odd number
    return m_data->visibleCount;
}

void QskFlowView::setVisibleCount( int count )
{
    m_data->visibleCount = count;
}

int QskFlowView::currentIndex() const
{
    return m_data->currentIndex;
}

void QskFlowView::setCurrentIndex( int index )
{
    if( index != m_data->currentIndex )
    {
        m_data->currentIndex = index;
        Q_EMIT currentIndexChanged();
    }
}

int QskFlowView::count() const
{
    return m_data->count;
}

void QskFlowView::setCount(int count)
{
    m_data->count = count;
}

double QskFlowView::swipeOffset() const
{
    return m_data->swipeOffset;
}

void QskFlowView::setSwipeOffset( double offset )
{
//    if( qFuzzyIsNull(offset))
//        qDebug() << "--- updating swipe offset";

    m_data->swipeOffset = offset;
    update();
}

qreal QskFlowView::currentItemWidth() const
{
    auto radians = qDegreesToRadians( angle() );
    qreal scaleFactor = qCos( radians );
    auto width = contentsRect().width() / ( 1 + ( visibleCount() - 1 ) * scaleFactor );

    return width;
}

void QskFlowView::adjustIndexAndSwipeOffset()
{
    const auto nodesSwipeOffset = swipeOffset() / currentItemWidth();
    auto newIndex = qRound( m_data->oldIndex - nodesSwipeOffset );
    newIndex = qMin( newIndex, count() - 1 );
    newIndex = qMax( newIndex, 0 );
    setCurrentIndex( newIndex );
    setSwipeOffset( 0 );
}

int QskFlowView::oldIndex() const
{
    return m_data->oldIndex;
}

void QskFlowView::gestureEvent( QskGestureEvent* event )
{
    // ### Shouldn't we be getting a swipe gesture?

    if ( event->gesture()->type() == QskGesture::Pan )
    {
        const auto gesture = static_cast< const QskPanGesture* >( event->gesture() );
        switch ( gesture->state() )
        {
            case QskGesture::Started:
            {
                auto deltaX = gesture->delta().x();
                // ### there is something wrong when starting a swipe while another one is in progress
                setSwipeOffset( deltaX );
                m_data->oldIndex = currentIndex();
                break;
            }
            case QskGesture::Updated:
            {
                setSwipeOffset( swipeOffset() + gesture->delta().x() );
                update();
                break;
            }
            case QskGesture::Finished:
            {
                const auto velocity = ( m_data->swipeOffset < 0.0 ) ? -gesture->velocity() : gesture->velocity();
                m_data->flicker.setWindow( window() );
                m_data->flicker.accelerate( gesture->angle(), velocity );
                break;
            }
            case QskGesture::Canceled:
            {
                // what to do here: maybe going back to the origin of the gesture ??
                break;
            }
            default:
                break;
        }

        return;
    }

    QskControl::gestureEvent( event );
}

bool QskFlowView::gestureFilter( QQuickItem* item, QEvent* event )
{
    // ### some stuff here is just commented out, check what to do with it:

    if ( event->type() == QEvent::MouseButtonPress )
    {
        // Checking first if panning is possible at all

        bool maybeGesture = false;

        const auto orientations = m_data->panRecognizer.orientations();
        if ( orientations )
        {
//            const QSizeF viewSize = viewContentsRect().size();
//            const QSizeF& scrollableSize = m_data->scrollableSize;

            if ( orientations & Qt::Vertical )
            {
//                if ( viewSize.height() < scrollableSize.height() )
                    maybeGesture = true;
            }

            if ( orientations & Qt::Horizontal )
            {
//                if ( viewSize.width() < scrollableSize.width() )
                    maybeGesture = true;
            }
        }

        if ( !maybeGesture )
            return false;
    }

    /*
        This code is a bit tricky as the filter is called in different situations:

        a) The press was on a child of the view
        b) The press was on the view

        In case of b) things are simple and we can let the recognizer
        decide without timeout if it is was a gesture or not.

        In case of a) we give the recognizer some time to decide - usually
        based on the distances of the following mouse events. If no decision
        could be made the recognizer aborts and replays the mouse events, so
        that the children can process them.

        But if a child does not accept a mouse event it will be sent to
        its parent. So we might finally receive the reposted events, but then
        we can proceed as in b).
     */

    auto& recognizer = m_data->panRecognizer;

    if ( event->type() == QEvent::MouseButtonPress )
    {
        if ( ( item != this ) && ( recognizer.timeout() < 0 ) )
        {
            const auto mouseEvent = static_cast< QMouseEvent* >( event );

            if ( recognizer.hasProcessedBefore( mouseEvent ) )
                return false;
        }

//        recognizer.setTimeout( ( item == this ) ? -1 : m_data->panRecognizerTimeout );
    }

    return m_data->panRecognizer.processEvent( item, event );
}
