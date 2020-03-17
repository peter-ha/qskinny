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
//    QQuickOpenGLShaderEffectNode* shaderNode = static_cast< QQuickOpenGLShaderEffectNode* >( node );
    QSGGeometryNode* shaderNode = static_cast< QSGGeometryNode* >( node );

    if( !shaderNode )
    {
//        shaderNode = new QQuickOpenGLShaderEffectNode;
        shaderNode = new QSGGeometryNode;

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor( Qt::cyan );
//        shaderNode->setMaterial( new QQuickOpenGLShaderEffectMaterial( shaderNode ) );
        shaderNode->setMaterial( material );
        shaderNode->setFlag( QSGNode::OwnsMaterial, true );

        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setDrawingMode(GL_LINES);
        geometry->setLineWidth(5);
        geometry->vertexDataAsPoint2D()[0].set(0, shaderEffect->height());
        geometry->vertexDataAsPoint2D()[1].set(shaderEffect->width(), 0 );

        shaderNode->setGeometry( geometry );
        shaderNode->setFlag( QSGNode::OwnsGeometry, true );

//        QObject::connect(shaderNode, &QQuickOpenGLShaderEffectNode::logAndStatusChanged,
//                []( const QString& log, int status ) {
//            qDebug() << "log and status changed" << log << status;
//        });
        // ### other stuff that shader effect is doing
    }

    qDebug() << "@@@" << static_cast<QSGGeometryNode*>( shaderNode );
    return shaderNode;
}

#include "moc_QskShaderEffectSkinlet.cpp"
