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
"                                uniform highp mat4 qt_Matrix;"
"                                attribute highp vec4 qt_Vertex;"
"                                attribute highp vec2 qt_MultiTexCoord0;"
"                                varying highp vec2 coord;"
"                                void main() {"
"                                    coord = qt_MultiTexCoord0;"
"                                    gl_Position = qt_Matrix * qt_Vertex;"
"                                }";
        shaderCode.sourceCode[ QQuickOpenGLShaderEffectMaterialKey::FragmentShader ] =
"                varying highp vec2 coord;"
"                uniform sampler2D src;"
"                uniform lowp float qt_Opacity;"
"                void main() {"
"                    lowp vec4 tex = texture2D(src, coord);"
"                    gl_FragColor = vec4(vec3(dot(tex.rgb,"
"                                        vec3(0.344, 0.5, 0.156))),"
"                                             tex.a) * qt_Opacity;"
"                }";
        material->setProgramSource( shaderCode );
        shaderNode->setMaterial( material );
        shaderNode->setFlag( QSGNode::OwnsMaterial, true );

        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setDrawingMode(GL_LINES);
        geometry->setLineWidth(3);
        geometry->vertexDataAsPoint2D()[0].set(0, 0);
        geometry->vertexDataAsPoint2D()[1].set(shader->width(), shader->height());
        shaderNode->setGeometry( geometry );
    }

    return shaderNode;
}

#include "moc_QskShaderEffectItemSkinlet.cpp"
