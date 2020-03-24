/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskPushButton.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* outerBox  = new QskLinearBox( Qt::Vertical );
    outerBox->setMargins( 10 );
    outerBox->setSpacing( 10 );

    auto* topBar = new QskLinearBox( Qt::Horizontal, outerBox );
    topBar->setSpacing( 10 );

    auto* topLabel1 = new QskTextLabel( "top bar label 1", topBar );
    topLabel1->setMargins( 10 );
    topLabel1->setBackgroundColor( Qt::magenta );

    auto* topLabel2 = new QskTextLabel( "top bar label 2", topBar );
    topLabel2->setMargins( 10 );
    topLabel2->setBackgroundColor( Qt::magenta );

    auto* topLabel3 = new QskTextLabel( "top bar label 3", topBar );
    topLabel3->setMargins( 10 );
    topLabel3->setBackgroundColor( Qt::magenta );


    auto* mainBox = new QskLinearBox( Qt::Horizontal, outerBox );

    auto* menuBox = new QskLinearBox( Qt::Vertical, mainBox );

    auto* menuLabel1 = new QskTextLabel( "menu 1", menuBox );
    menuLabel1->setMargins( 10 );
    menuLabel1->setBackgroundColor( Qt::cyan );

    auto* menuLabel2 = new QskTextLabel( "menu 2", menuBox );
    menuLabel2->setMargins( 10 );
    menuLabel2->setBackgroundColor( Qt::cyan );

    auto* menuLabel3 = new QskTextLabel( "menu 3", menuBox );
    menuLabel3->setMargins( 10 );
    menuLabel3->setBackgroundColor( Qt::cyan );

    auto* mainText = new QskTextLabel( "here main area", mainBox );
    mainText->setSizePolicy( Qt::Horizontal, QskSizePolicy::Expanding );

    QskWindow window;
    window.addItem( outerBox );
    window.show();

    return app.exec();
}
