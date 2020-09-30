#ifndef LIGHTINTENSITY_H
#define LIGHTINTENSITY_H

#include "Box.h"

#include <QQuickPaintedItem>
#include <QRadialGradient>

class DimmerAnimator;
class QskTextLabel;

class LightDimmer: public QQuickPaintedItem
{
        Q_OBJECT

    public:
        LightDimmer( QQuickItem* parent );

        double thickness() const
        {
            return m_thickness;
        }

        void setThickness( double thickness )
        {
            m_thickness = thickness;
        }

        QColor backgroundColor() const
        {
            return m_backgroundColor;
        }

        void setBackgroundColor( const QColor& color )
        {
            m_backgroundColor = color;
        }

        QRadialGradient ringGradient() const
        {
            return m_ringGradient;
        }

        void setRingGradient( const QRadialGradient& gradient )
        {
            m_ringGradient = gradient;
        }

    private:
        double m_thickness = 17.57;
        QColor m_backgroundColor;
        QRadialGradient m_ringGradient;

        virtual void paint( QPainter* painter ) override;
};

class LightDisplay : public QskControl
{
        Q_OBJECT

    public:
        QSK_SUBCONTROLS( Panel )

        LightDisplay( QQuickItem* parent );

        QskAspect::Subcontrol effectiveSubcontrol(
            QskAspect::Subcontrol subControl ) const override final;

    protected:
        void updateLayout() override;

    private:
        QskTextLabel* m_leftLabel;
        QskTextLabel* m_centreLabel;
        QskTextLabel* m_rightLabel;
        LightDimmer* m_dimmer;
        DimmerAnimator* m_animator;
};

class LightIntensity : public Box
{
        Q_OBJECT

    public:
        LightIntensity( QQuickItem* parent );
};

#endif // LIGHTINTENSITY_H
