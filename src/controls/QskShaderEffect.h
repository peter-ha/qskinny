#ifndef QSKSHADEREFFECT_H
#define QSKSHADEREFFECT_H

#include "QskControl.h"

class QSK_EXPORT QskShaderEffect : public QskControl
{
    Q_OBJECT

    using Inherited = QskControl;

public:
    QSK_SUBCONTROLS( Panel )

    QskShaderEffect( QQuickItem* parent = nullptr );
    ~QskShaderEffect() override;

    void setSource( QskControl* source );

protected:
    QSizeF contentsSizeHint( Qt::SizeHint, const QSizeF& ) const override;

  private:
    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

#endif // QSKSHADEREFFECT_H
