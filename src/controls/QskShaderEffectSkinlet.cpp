#include "QskShaderEffectSkinlet.h"
#include "QskShaderEffect.h"

QskShaderEffectSkinlet::QskShaderEffectSkinlet( QskSkin* skin )
    : Inherited( skin )
{
    setNodeRoles( { PanelRole } );

    qDebug() << "@@@" << Q_FUNC_INFO;
}

QskShaderEffectSkinlet::~QskShaderEffectSkinlet()
{
}

QSGNode* QskShaderEffectSkinlet::updateSubNode(
    const QskSkinnable* skinnable, quint8 nodeRole, QSGNode* node ) const
{
    const auto shaderEffect = static_cast< const QskShaderEffect* >( skinnable );

    switch ( nodeRole )
    {
        case PanelRole:
        {
            return updateShaderNode( shaderEffect, node );
        }
    }

    return Inherited::updateSubNode( skinnable, nodeRole, node );
}

QSGNode* QskShaderEffectSkinlet::updateShaderNode( const QskShaderEffect*, QSGNode* ) const
{
    return nullptr;
}

#include "moc_QskShaderEffectSkinlet.cpp"
