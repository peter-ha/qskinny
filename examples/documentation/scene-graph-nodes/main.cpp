/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskPushButton.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    // Toggle the adding of the box to check the difference
    // of the scene graph nodes created:
    auto* box = new QskBox;
    box->setAutoLayoutChildren( true );

    auto* button = new QskPushButton( "button", box );

    QskWindow window;
    window.addItem( box );
    window.show();

    return app.exec();
}
