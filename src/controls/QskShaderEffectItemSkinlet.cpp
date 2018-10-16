#include "QskShaderEffectItemSkinlet.h"
#include "QskShaderEffectItem.h"

#include <private/qquickopenglshadereffectnode_p.h>

QskShaderEffectItemSkinlet::QskShaderEffectItemSkinlet( QskSkin *skin ) : Inherited( skin )
{
    setNodeRoles( { ShaderRole } );
}

QskShaderEffectItemSkinlet::~QskShaderEffectItemSkinlet() = default;

QRectF QskShaderEffectItemSkinlet::subControlRect( const QskSkinnable* skinnable, QskAspect::Subcontrol subControl ) const
{
    return Inherited::subControlRect( skinnable, subControl );
}

QSGNode* QskShaderEffectItemSkinlet::updateSubNode( const QskSkinnable* skinnable, quint8 nodeRole, QSGNode* node ) const
{
    const auto shader = static_cast< const QskShaderEffectItem* >( skinnable );

    switch ( nodeRole )
    {
        case ShaderRole:
        {
            return updateShaderNode( shader, node );
        }
    }

    return Inherited::updateSubNode( skinnable, nodeRole, node );
}

QSGNode* QskShaderEffectItemSkinlet::updateShaderNode( const QskShaderEffectItem* shader, QSGNode* node ) const
{
    auto shaderNode = static_cast< QQuickOpenGLShaderEffectNode* >( node );

    if ( shaderNode == nullptr )
    {
        shaderNode = new QQuickOpenGLShaderEffectNode;
        auto material = new QQuickOpenGLShaderEffectMaterial( shaderNode );
        QQuickOpenGLShaderEffectMaterialKey shaderCode;
        shaderCode.sourceCode[ QQuickOpenGLShaderEffectMaterialKey::VertexShader ] =
"                uniform highp mat4 qt_Matrix;"
"                "
"                attribute highp vec4 qt_Vertex;"
"                attribute highp vec2 qt_MultiTexCoord0;"
"                "
"                varying highp vec2 qt_TexCoord0;"
"                "
"                void main()"
"                {"
"                    qt_TexCoord0 = qt_MultiTexCoord0;"
"                    gl_Position = qt_Matrix * qt_Vertex;"
"                }";
        shaderCode.sourceCode[ QQuickOpenGLShaderEffectMaterialKey::FragmentShader ] =
"                varying highp vec2 qt_TexCoord0;"
"                "
"                uniform sampler2D source;"
"                uniform lowp float qt_Opacity;"
"                "
"                void main()"
"                {"
"                    gl_FragColor = texture2D(source, qt_TexCoord0) * qt_Opacity;"
"                }";
        material->setProgramSource( shaderCode );
        material->attributes = { "qt_Vertex"  "qt_MultiTexCoord0" };
        shaderNode->setMaterial( material );
        shaderNode->setFlag( QSGNode::OwnsMaterial, true );

        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        geometry->setLineWidth(3);
        geometry->vertexDataAsPoint2D()[0].set(0, 0);
        geometry->vertexDataAsPoint2D()[1].set( 300, 0 );
        geometry->vertexDataAsPoint2D()[2].set( 0, 300 );
        shaderNode->setGeometry( geometry );

        geometry->markVertexDataDirty();
        shaderNode->markDirty( QSGNode::DirtyGeometry );
        shaderNode->markDirty( QSGNode::DirtyMaterial );
    }

    return shaderNode;
}

#include "moc_QskShaderEffectItemSkinlet.cpp"
