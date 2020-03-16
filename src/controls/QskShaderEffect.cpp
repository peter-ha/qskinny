#include "QskShaderEffect.h"

QSK_SUBCONTROL( QskShaderEffect, Panel )

class QskShaderEffect::PrivateData
{
  public:
    PrivateData()
    {
    }

    QskControl* source = nullptr;
};

QskShaderEffect::QskShaderEffect( QQuickItem* parent )
    : Inherited( parent )
    , m_data( new PrivateData() )
{
}

QskShaderEffect::~QskShaderEffect()
{
}

void QskShaderEffect::setSource( QskControl* source )
{
    m_data->source = source;
}

QSizeF QskShaderEffect::contentsSizeHint( Qt::SizeHint which, const QSizeF& constraint ) const
{
    if( m_data->source != nullptr )
    {
        return m_data->source->implicitSizeHint( which, constraint );
    }

    return QSizeF();
}

#include "moc_QskShaderEffect.cpp"
