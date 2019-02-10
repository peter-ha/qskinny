#ifndef QSKFLOWVIEW_H
#define QSKFLOWVIEW_H

#include "QskControl.h"
#include "QskPanGestureRecognizer.h"
#include "QskNamespace.h"

class QskFlowView : public QskControl
{
    Q_OBJECT

  public:
    QskFlowView( QQuickItem* parent = nullptr );
    ~QskFlowView() override;

    qreal angle() const;
    void setAngle( qreal angle );

    int visibleCount() const;
    void setVisibleCount( int count );

    int currentIndex() const;
    void setCurrentIndex( int index );

    int count() const;
    void setCount( int count );

    double swipeOffset() const;

    // ### make it possible to set the width?
    virtual qreal currentItemWidth() const;

    virtual QSGNode* nodeAt( int index, QSGNode* oldNode ) const = 0;

protected:
    void gestureEvent( QskGestureEvent* ) override;
    bool gestureFilter( QQuickItem*, QEvent* ) override;

  private:
    qreal m_angle = 30;
    int m_visibleCount = 5;
    int m_currentIndex = -1;
    int m_oldIndex = -1;
    int m_count = 0;

    double m_swipeOffset = 0;
    Qsk::Direction m_swipeDirection = Qsk::TopToBottom; // initialize with impossible value
    QskPanGestureRecognizer m_panRecognizer;
};

#endif // QSKFLOWVIEW_H
