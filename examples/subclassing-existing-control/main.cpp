/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskMargins.h>
#include <QskSetup.h>
#include <QskSkin.h>
#include <QskSkinFactory.h>
#include <QskSkinManager.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

class TextLabel : public QskTextLabel
{

    Q_OBJECT

public:
    QSK_SUBCONTROLS( Panel )

    TextLabel( const QString& text, QQuickItem* parent = nullptr ) : QskTextLabel( text, parent )
    {
        setPanel( true );

        // for simple example comment in:
//        setMargins( 15 );
//        setBackgroundColor( Qt::cyan );
    }

    QskAspect::Subcontrol effectiveSubcontrol( QskAspect::Subcontrol subControl ) const override final
    {
        if ( subControl == QskTextLabel::Panel )
            return TextLabel::Panel;

        return subControl;
    }
};

QSK_SUBCONTROL( TextLabel, Panel )

class MySkin : public QskSkin
{

public:
    MySkin( QObject* parent = nullptr ) : QskSkin( parent )
    {
        setGradient( TextLabel::Panel, Qt::cyan );
        setMargins( TextLabel::Panel | QskAspect::Padding, 15 );
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

    auto* customLabel = new TextLabel( "control 1" );

    QskWindow window;
    window.addItem( customLabel );
    window.show();

    return app.exec();
}

#include "main.moc"
