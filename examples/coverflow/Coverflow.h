/******************************************************************************
 * QSkinny - Copyright (C) 2018 Peter Hartmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef COVERFLOW_H
#define COVERFLOW_H

#include <QskNamespace.h>
#include <QskScrollView.h>
#include <QskGraphicLabel.h>
#include <QskPanGestureRecognizer.h>

class Coverflow : public QskControl
{
    Q_OBJECT

public:
    Coverflow( QQuickItem* parentItem = nullptr );

    void addCover( QskGraphicLabel* cover );

    QskGraphicLabel* activeCover() const;
    void setActiveCover( QskGraphicLabel* cover ); // ### or maybe set the index?
    void setMaxCoversOnEachSide( int num );

protected:
    virtual void updateLayout() override;
    void gestureEvent( QskGestureEvent* ) override;
    bool gestureFilter( QQuickItem*, QEvent* ) override;

private:
    QSizeF coverSize( int index ) const;

    QVector< QskGraphicLabel* > m_covers; // ### could make this QskControls actually
    int m_activeCoverIndex = -1;
    double m_swipeOffset = 0;
    int m_maxCoversOnEachSide = 2;
    Qsk::Direction m_swipeDirection;
    QskPanGestureRecognizer m_panRecognizer;
};

#endif
