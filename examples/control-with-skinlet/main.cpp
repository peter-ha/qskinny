/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskBoxNode.h>
#include <QskBoxBorderColors.h>
#include <QskBoxBorderMetrics.h>
#include <QskBoxShapeMetrics.h>
#include <QskLinearBox.h>
#include <QskSetup.h>
#include <QskSkin.h>
#include <QskSkinFactory.h>
#include <QskSkinlet.h>
#include <QskSkinManager.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

class CustomShape : public QskControl
{
    Q_OBJECT

public:
    QSK_SUBCONTROLS( Panel, InnerShape )

    CustomShape( QQuickItem* parent = nullptr ) : QskControl( parent )
    {
    }
};

QSK_SUBCONTROL( CustomShape, Panel )
QSK_SUBCONTROL( CustomShape, InnerShape )

class CustomShapeSkinlet : public QskSkinlet
{
    Q_GADGET

public:
    enum NodeRole
    {
        PanelRole, InnerShapeRole
    };

    Q_INVOKABLE CustomShapeSkinlet( QskSkin* skin = nullptr ) : QskSkinlet( skin )
    {
        setNodeRoles( { PanelRole, InnerShapeRole } );
    }

    ~CustomShapeSkinlet() override
    {
    }

    QRectF subControlRect( const QskSkinnable* skinnable, const QRectF& contentsRect, QskAspect::Subcontrol subControl ) const override
    {
        const auto customShape = static_cast< const CustomShape* >( skinnable );

        if ( subControl == CustomShape::Panel )
        {
            return contentsRect;
        }
        else if ( subControl == CustomShape::InnerShape )
        {
            const auto margins = customShape->marginsHint( CustomShape::InnerShape );
            return contentsRect.marginsRemoved( margins );
        }

        return QskSkinlet::subControlRect( skinnable, contentsRect, subControl );
    }

protected:
    QSGNode* updateSubNode( const QskSkinnable* skinnable, quint8 nodeRole, QSGNode* node ) const override
    {
        const auto* customShape = static_cast< const CustomShape* >( skinnable );

        switch ( nodeRole )
        {
            case PanelRole:
            {
                auto panelNode = static_cast< QskBoxNode* >( node );

                if ( panelNode == nullptr )
                {
                    panelNode = new QskBoxNode;
                }

                const auto panelRect = subControlRect( customShape, customShape->contentsRect(), CustomShape::Panel );

                const qreal radius = panelRect.width() / 2;

                QskBoxShapeMetrics shapeMetrics( radius );
                QskBoxBorderMetrics borderMetrics = customShape->boxBorderMetricsHint( CustomShape::Panel );
                QskBoxBorderColors borderColors = customShape->boxBorderColorsHint( CustomShape::Panel );
                QskGradient gradient = customShape->gradientHint( CustomShape::Panel );
                panelNode->setBoxData( panelRect, shapeMetrics, borderMetrics, borderColors, gradient );

                return panelNode;
            }
            case InnerShapeRole:
            {
                auto innerNode = static_cast< QskBoxNode* >( node );

                if ( innerNode == nullptr )
                {
                    innerNode = new QskBoxNode;
                }

                const auto innerRect = subControlRect( customShape, customShape->contentsRect(), CustomShape::InnerShape );
                const qreal radius = innerRect.width() / 2;

                QskBoxShapeMetrics shapeMetrics( radius );
                QskBoxBorderMetrics borderMetrics = customShape->boxBorderMetricsHint( CustomShape::Panel );
                QskBoxBorderColors borderColors = customShape->boxBorderColorsHint( CustomShape::Panel );
                QskGradient gradient = customShape->gradientHint( CustomShape::InnerShape );
                innerNode->setBoxData( innerRect, shapeMetrics, borderMetrics, borderColors, gradient );

                return innerNode;
            }
        }

        return QskSkinlet::updateSubNode( skinnable, nodeRole, node );
    }
};

class MySkin : public QskSkin
{

public:
    MySkin( QObject* parent = nullptr ) : QskSkin( parent )
    {
       declareSkinlet< CustomShape, CustomShapeSkinlet >();

       setGradient( CustomShape::Panel, Qt::blue );
       setMargins( CustomShape::InnerShape, 20 );
       setGradient( CustomShape::InnerShape, Qt::magenta );
    }
};

class MySkinFactory : public QskSkinFactory
{

    Q_OBJECT

public:
    QStringList skinNames() const override
    {
        return { "MySkin" };
    }

    QskSkin* createSkin( const QString& /*skinName*/ ) override
    {
        return new MySkin();
    }
};

int main( int argc, char* argv[] )
{
    auto skinFactory = new MySkinFactory();
    qskSkinManager->registerFactory( QStringLiteral( "MySkinFactory" ), skinFactory );

    QGuiApplication app( argc, argv );

    qskSetup->setSkin( QStringLiteral( "MySkin" ) );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* customShape = new CustomShape;

    QskWindow window;
    window.addItem( customShape );
    window.show();

    return app.exec();
}

#include "main.moc"
