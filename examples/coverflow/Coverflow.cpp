/******************************************************************************
 * QSkinny - Copyright (C) 2018 Peter Hartmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "Coverflow.h"

#include <QskEvent.h>
#include <QskGesture.h>
#include <QskGraphic.h>

#include <QImage>

#include <cmath>

Coverflow::Coverflow( QQuickItem* parentItem )
    : QskControl( parentItem )
{
    setPolishOnResize( true );

    m_panRecognizer.setOrientations( Qt::Horizontal );
    m_panRecognizer.setWatchedItem( this );

    setAcceptedMouseButtons( Qt::LeftButton ); // to get gesture events from the mouse as well
}

void Coverflow::addCover( QskGraphicLabel* cover )
{
    m_covers.append( cover );

    // set index automatically to the element in the middle:
    m_activeCoverIndex = m_covers.count() / 2;
}

QskGraphicLabel* Coverflow::activeCover() const
{
    if( m_activeCoverIndex == -1 )
        return nullptr;

    Q_ASSERT( m_activeCoverIndex < m_covers.count() );
    return m_covers.at( m_activeCoverIndex );
}

void Coverflow::setActiveCover( QskGraphicLabel* cover )
{
    m_activeCoverIndex = m_covers.indexOf( cover );

    if( m_activeCoverIndex == -1 )
        qWarning( "could not set active cover" );
}

void Coverflow::setMaxCoversOnEachSide( int num )
{
    m_maxCoversOnEachSide = num;
}

void Coverflow::updateLayout()
{
    // first, place the active cover:
    const auto bigCoverWidth = height() - 50; // ### style
    const auto activeCoverX = ( size().width() - bigCoverWidth  ) / 2;

    auto stepX = activeCoverX / m_maxCoversOnEachSide;
    auto smallCoverWidth = stepX - 5; // ### use a hardcoded value through the style

    auto swipedToCoverIndex = -1;

    if( m_activeCoverIndex > 0 && m_activeCoverIndex < m_covers.count() - 1 )
    {
        swipedToCoverIndex = ( m_swipeOffset > 0 ) ? m_activeCoverIndex - 1 : m_activeCoverIndex + 1;
    }

    // ### something is not completely right about the fraction
    const auto fraction = m_swipeOffset / bigCoverWidth;

    // assume a linear width between active and non active cover for now:
    const auto widthDiff = std::abs( bigCoverWidth - smallCoverWidth );
    auto activeCoverWidth = bigCoverWidth - std::abs( fraction ) * widthDiff;
    activeCoverWidth = qMax( activeCoverWidth, smallCoverWidth );
    qDebug() << activeCoverWidth << bigCoverWidth;

    const auto activeCoverY = ( size().height() - activeCoverWidth ) / 2;
    auto swipedToCoverWidth = smallCoverWidth + std::abs( fraction ) * widthDiff;
    swipedToCoverWidth = qMin( swipedToCoverWidth, bigCoverWidth );

    auto leftXOffset = ( swipedToCoverIndex > -1 && swipedToCoverIndex < m_activeCoverIndex ) ? ( swipedToCoverWidth - smallCoverWidth ) : 0;

    if( m_activeCoverIndex != -1 )
    {
        auto activeCover = m_covers.at( m_activeCoverIndex );
        activeCover->setGeometry( activeCoverX + leftXOffset, activeCoverY, activeCoverWidth, activeCoverWidth );
    }

    // then, place the covers left of the active one:
    auto y = activeCoverY + ( activeCoverWidth - swipedToCoverWidth ) / 2;

    for( int a = 1; a <= m_maxCoversOnEachSide; a++ )
    {
        auto index = m_activeCoverIndex - a;

        if( index < 0 )
            break;

        auto x = ( m_maxCoversOnEachSide - a ) * stepX;
        auto yOffset = ( index == swipedToCoverIndex ) ? 0 : ( swipedToCoverWidth - smallCoverWidth ) / 2;
        auto cover = m_covers.at( index );
        // ### we could only set the position here and only set the size once
        cover->setVisible( true );
        auto width = ( index == swipedToCoverIndex ) ? swipedToCoverWidth : smallCoverWidth;
        cover->setGeometry( x, y + yOffset, width, width );
    }

    // make covers invisible that are out of range on the right side:

    // ### For a large number of covers this is inefficient, we should only change
    // visibility for 2 elements per function call
    for( int index = m_activeCoverIndex - m_maxCoversOnEachSide - 1; index >= 0; index-- )
    {
        auto cover = m_covers.at( index );
        cover->setVisible( false );
    }

    // then, place the covers right of the active one:
    for( int a = 1; a <= m_maxCoversOnEachSide; a++ )
    {
        auto index = m_activeCoverIndex + a;

        if( index >= m_covers.count() )
            break;

        auto x = ( m_maxCoversOnEachSide + ( a - 1 ) ) * stepX + activeCoverWidth + 5;

        auto xOffset = ( index > swipedToCoverIndex ) ? ( swipedToCoverWidth - smallCoverWidth ) : 0;

        auto yOffset = ( index == swipedToCoverIndex ) ? 0 : ( swipedToCoverWidth - smallCoverWidth ) / 2;
        auto cover = m_covers.at( index );

        // ### we could only set the position here and only set the size once
        cover->setVisible( true );
        auto width = ( index == swipedToCoverIndex ) ? swipedToCoverWidth : smallCoverWidth;
        cover->setGeometry( x + xOffset, y + yOffset, width, width );
    }

    // make covers invisible that are out of range on the right side:

    // ### For a large number of covers this is inefficient, we should only change
    // visibility for 2 elements per function call
    for( int index = m_activeCoverIndex + m_maxCoversOnEachSide + 1; index < m_covers.count(); index++ )
    {
        auto cover = m_covers.at( index );
        cover->setVisible( false );
    }
}

void Coverflow::gestureEvent( QskGestureEvent* event )
{
    // ### Shouldn't we be getting a swipe gesture?

    if ( event->gesture()->type() == QskGesture::Pan )
    {
        const auto gesture = static_cast< const QskPanGesture* >( event->gesture() );
        switch ( gesture->state() )
        {
            case QskGesture::Started:
            {
                m_swipeDirection = ( gesture->delta().x() < 0 ) ? Qsk::RightToLeft : Qsk::LeftToRight;
                break;
            }
            case QskGesture::Updated:
            {
                // ### Try this: If velocity is above a certain threshold, swipe
                // fast through all covers, otherwise swipe to the next one

                auto v = gesture->velocity();

                if( v > 3500 || v < -3500 )
                {
                    qDebug() << "fast swipe";
                    // ### here implement fast swipe
                }
                else
                {
                    m_swipeOffset += gesture->delta().x();
                    polish();
                }
                break;
            }
            case QskGesture::Finished:
            {
                m_swipeOffset = 0;

                if( m_swipeDirection == Qsk::LeftToRight )
                {
                    if( m_activeCoverIndex > 0 )
                    {
                        m_activeCoverIndex--;
                        polish();
                    }
                }
                else
                {
                    if( m_activeCoverIndex < m_covers.count() - 1 )
                    {
                        m_activeCoverIndex++;
                        polish();
                    }

                }

                // ### here align covers

//                m_data->flicker.setWindow( window() );
//                m_data->flicker.accelerate( gesture->angle(), gesture->velocity() );
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

bool Coverflow::gestureFilter( QQuickItem* item, QEvent* event )
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        // Checking first if panning is possible at all

        bool maybeGesture = false;

        const auto orientations = m_panRecognizer.orientations();
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

    auto& recognizer = m_panRecognizer;

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

    return m_panRecognizer.processEvent( item, event );
}

QSizeF Coverflow::coverSize( int index ) const
{

}
