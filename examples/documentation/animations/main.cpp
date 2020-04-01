/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskAnimationHint.h>
#include <QskMargins.h>
#include <QskPushButton.h>
#include <QskSetup.h>
#include <QskSkin.h>
#include <QskSkinFactory.h>
#include <QskSkinManager.h>
#include <QskWindow.h>

#include <QGuiApplication>

class MySkin : public QskSkin
{

public:
    MySkin( QObject* parent = nullptr ) : QskSkin( parent )
    {
        setGradient( QskPushButton::Panel, Qt::magenta );
        setMargins( QskPushButton::Panel | QskAspect::Padding, 10 );
        setColor( QskPushButton::Text, Qt::black );
        setGradient( QskPushButton::Panel | QskPushButton::Hovered, Qt::cyan );
        setAnimation( QskPushButton::Panel | QskAspect::Color, 1000 );
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
        return new MySkin;
    }
};

int main( int argc, char* argv[] )
{
    auto* skinFactory = new MySkinFactory;
    qskSkinManager->setPluginPaths( QStringList() ); // no default plugins

    qskSkinManager->registerFactory( "MySkinFactory", skinFactory );

    QGuiApplication app( argc, argv );

    qskSetup->setSkin( "MySkin" );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* button = new QskPushButton( "button" );

    QskWindow window;
    window.addItem( button );
    window.show();

    return app.exec();
}

#include "main.moc"
