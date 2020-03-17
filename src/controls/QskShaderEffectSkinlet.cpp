#include "QskShaderEffectSkinlet.h"
#include "QskShaderEffect.h"

#include <private/qquickopenglshadereffectnode_p.h>
#include <qsgflatcolormaterial.h> // ### remove

QskShaderEffectSkinlet::QskShaderEffectSkinlet( QskSkin* skin )
    : Inherited( skin )
{
    setNodeRoles( { PanelRole } );
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

QSGNode* QskShaderEffectSkinlet::updateShaderNode( const QskShaderEffect* shaderEffect, QSGNode* node ) const
{
    QQuickOpenGLShaderEffectNode* shaderNode = static_cast< QQuickOpenGLShaderEffectNode* >( node );

    if( !shaderNode )
    {
        shaderNode = new QQuickOpenGLShaderEffectNode;

        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setDrawingMode(GL_LINES);
        geometry->setLineWidth(5);
        geometry->vertexDataAsPoint2D()[0].set(0, shaderEffect->height());
        geometry->vertexDataAsPoint2D()[1].set(shaderEffect->width(), 0 );

        shaderNode->setGeometry( geometry );
        shaderNode->setFlag( QSGNode::OwnsGeometry, true );

        auto* material = new QQuickOpenGLShaderEffectMaterial( shaderNode );

        QQuickOpenGLShaderEffectMaterialKey source;
        source.sourceCode[QQuickOpenGLShaderEffectMaterialKey::VertexShader] = "uniform highp mat4 qt_Matrix;\n"
            "attribute highp vec4 qt_Vertex;\n"
            "attribute highp vec2 qt_MultiTexCoord0;\n"
            "varying highp vec2 coord;\n"
            "void main() {\n"
            "    coord = qt_MultiTexCoord0;\n"
            "    gl_Position = qt_Matrix * qt_Vertex;\n"
            "}\n";
        source.sourceCode[QQuickOpenGLShaderEffectMaterialKey::FragmentShader] = "varying highp vec2 coord;\n"
            "uniform sampler2D src;\n"
            "uniform lowp float qt_Opacity;\n"
            "void main() {\n"
            "    lowp vec4 tex = texture2D(src, coord);\n"
            "    gl_FragColor = vec4(vec3(dot(tex.rgb,\n"
            "                        vec3(0.344, 0.5, 0.156))),\n"
            "                             tex.a) * qt_Opacity;\n"
            "}\n";
        material->setProgramSource( source );

        shaderNode->setMaterial( material );
        shaderNode->setFlag( QSGNode::OwnsMaterial, true );
        shaderNode->markDirty( QSGNode::DirtyMaterial );
    }

    qDebug() << "@@@" << static_cast<QSGGeometryNode*>( shaderNode );
    return shaderNode;
}

#include "moc_QskShaderEffectSkinlet.cpp"
