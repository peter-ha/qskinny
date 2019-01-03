#ifndef QSKFLOWVIEW_H
#define QSKFLOWVIEW_H

#include <QskControl.h>

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

    // ### make it possible to set?
    virtual qreal currentItemWidth() const;

    virtual QSGNode* nodeAt( int index, QSGNode* oldNode ) const = 0;

  private:
    qreal m_angle;
    int m_visibleCount;
    int m_currentIndex;
};

#endif // QSKFLOWVIEW_H
