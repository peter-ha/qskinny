#ifndef CARD_H
#define CARD_H

#include <QskLinearBox.h>

class QskTextLabel;

class Box : public QskLinearBox
{
        Q_OBJECT
    public:
        QSK_SUBCONTROLS( Panel )

        Box( const QString& title, QQuickItem* parent );

        QskAspect::Subcontrol effectiveSubcontrol(
            QskAspect::Subcontrol subControl ) const override;

    private:
        QString m_title;
        QskTextLabel* m_label;
        QskControl* m_content;
};

#endif // CARD_H
