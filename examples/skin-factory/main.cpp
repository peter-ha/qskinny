/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskBoxBorderColors.h>
#include <QskBoxBorderMetrics.h>
#include <QskLinearBox.h>
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
    }
};

class OtherSkin : public QskSkin
{

public:
    OtherSkin( QObject* parent = nullptr ) : QskSkin( parent )
    {
        setGradient( QskPushButton::Panel, Qt::cyan );
        setMargins( QskPushButton::Panel | QskAspect::Padding, 15 );
        setBoxBorderColors( QskPushButton::Panel, Qt::blue );
        setBoxBorderMetrics( QskPushButton::Panel, 1 );
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
        if ( skinName == "MySkin" )
            return new MySkin;

        if ( skinName == "OtherSkin" )
            return new OtherSkin;

        return nullptr;
    }
};

int main( int argc, char* argv[] )
{
    auto skinFactory = new MySkinFactory();
    qskSkinManager->registerFactory( "MySkinFactory", skinFactory );
    qskSkinManager->setPluginPaths( QStringList() ); // no plugins

    QGuiApplication app( argc, argv );

    qskSetup->setSkin( "OtherSkin" );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* button = new QskPushButton( "button" );

    QskWindow window;
    window.addItem( button );
    window.show();

    return app.exec();
}

#include "main.moc"
