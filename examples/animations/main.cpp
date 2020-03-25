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
       setGradient( QskPushButton::Panel | QskPushButton::Pressed, Qt::yellow );
       setAnimation( QskPushButton::Panel | QskAspect::Color, 1000 );
    }
};

// actually, we don't need the other skin at all
class OtherSkin : public QskSkin
{

public:
    OtherSkin( QObject* parent = nullptr ) : QskSkin( parent )
    {
       setGradient( QskPushButton::Panel, Qt::cyan );
       setGradient( QskPushButton::Panel | QskPushButton::Pressed, Qt::green );
       setAnimation( QskPushButton::Panel | QskAspect::Color, 1000 );
    }
};

class MySkinFactory : public QskSkinFactory
{

    Q_OBJECT

public:
    QStringList skinNames() const override
    {
        return { "MySkin", "OtherSkin" };
    }

    QskSkin* createSkin( const QString& skinName ) override
    {
        if( skinName == "MySkin" )
            return new MySkin;

        else if( skinName == "OtherSkin" )
            return new OtherSkin;

        return nullptr;
    }
};

int main( int argc, char* argv[] )
{
    auto skinFactory = new MySkinFactory();
    qskSkinManager->setPluginPaths( QStringList() ); // no default plugins

    qskSkinManager->registerFactory( QStringLiteral( "MySkinFactory" ), skinFactory );

    QGuiApplication app( argc, argv );

    qskSetup->setSkin( QStringLiteral( "MySkin" ) );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* button = new QskPushButton( "button" );
    button->setExplicitSizeHint( Qt::PreferredSize, { 100, 50 } );

    QskWindow window;
    window.addItem( button );
    window.show();

    return app.exec();
}

#include "main.moc"
