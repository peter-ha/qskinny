#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Box.h"

#include <QQuickPaintedItem>

class DiagramContent;
class QskGridBox;

class WeekdayBox : public QskBox
{
        Q_OBJECT

    public:
        QSK_SUBCONTROLS( Panel )

        WeekdayBox( QQuickItem* parent ) : QskBox( true, parent )
        {
        }

        QskAspect::Subcontrol effectiveSubcontrol(
            QskAspect::Subcontrol subControl ) const override final
        {
            if( subControl == QskBox::Panel )
            {
                return WeekdayBox::Panel;
            }

            return subControl;
        }
};

class CaptionColorBox : public QskBox
{
        Q_OBJECT

    public:
        QSK_SUBCONTROLS( Panel )

        CaptionColorBox( QQuickItem* parent ) : QskBox( true, parent )
        {
        }

        QskAspect::Subcontrol effectiveSubcontrol(
            QskAspect::Subcontrol subControl ) const override final
        {
            if( subControl == QskBox::Panel )
            {
                return Panel;
            }

            return subControl;
        }
};

class CaptionItem : public QskLinearBox
{
        Q_OBJECT

    public:
        QSK_SUBCONTROLS( Panel )
        QSK_STATES( Water, Electricity, Gas )

        CaptionItem( QskAspect::State state, QQuickItem* parent );
};

class Diagram : public Box
{
        Q_OBJECT

    public:
        QSK_SUBCONTROLS( Panel )

        Diagram( QQuickItem* parent );
        void updateLayout() override;

        QskAspect::Subcontrol effectiveSubcontrol(
            QskAspect::Subcontrol subControl ) const override final
        {
            if( subControl == QskBox::Panel )
            {
                return Panel;
            }

            return subControl;
        }

    private:
        QskLinearBox* m_caption;
        QskGridBox* m_weekdays;
        DiagramContent* m_content;
};

class DiagramContent : public QQuickPaintedItem
{
        Q_OBJECT

    public:
        DiagramContent( QQuickItem* parent );

        virtual void paint( QPainter* painter ) override;

};

#endif // DIAGRAM_H
