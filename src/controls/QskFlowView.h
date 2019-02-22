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

    double swipeOffset() const; // ### rename to scrollPos() to make it consistent with QskScrollView?
    void setSwipeOffset( double offset );

    // ### make it possible to set the width?
    virtual qreal currentItemWidth() const;

    virtual QSGNode* nodeAt( int index, QSGNode* oldNode ) const = 0;

    void adjustIndexAndSwipeOffset(); // called by the flicker after a gesture finishes

    int oldIndex() const;

Q_SIGNALS:
    void currentIndexChanged();

protected:
    void gestureEvent( QskGestureEvent* ) override;
    bool gestureFilter( QQuickItem*, QEvent* ) override;

  private:
    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

#endif // QSKFLOWVIEW_H
