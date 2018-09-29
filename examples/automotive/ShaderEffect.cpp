#include "ShaderEffect.h"

#include <private/qquickshadereffectsource_p.h>

ShaderEffect::ShaderEffect( QQuickItem *parent ) : Inherited( parent  ),
    m_shaderEffectSource( new QQuickShaderEffectSource( parent  ) )
{
    Q_ASSERT( parent );

    // ### need to make this more flexible
    m_shaderEffectSource->setSourceItem( parent );
    m_shaderEffectSource->setRecursive( true ); // ### why do we need this?
    setProperty( "source", QVariant::fromValue( m_shaderEffectSource.get() ) );

    connect( parentItem(), &QQuickItem::widthChanged, [ this ]()
    {
        setWidth( parentItem()->width() );
    });

    connect( parentItem(), &QQuickItem::heightChanged, [ this ]()
    {
        setHeight( parentItem()->height() );
    });

    connect( this, &QQuickShaderEffect::statusChanged, [ this ]()
    {
        qDebug() << "shader status:" << status();
        if( !log().isEmpty() )
        {
            qDebug() << "log:" << log();
        }
    } );
}
