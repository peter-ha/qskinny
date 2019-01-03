/******************************************************************************
 * QSkinny - Copyright (C) 2018 Peter Hartmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "CoverflowSimpleExample.h"

#include <QGuiApplication>

#include <QskWindow.h>
#include <SkinnyShortcut.h>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );
    SkinnyShortcut::enable( SkinnyShortcut::Quit | SkinnyShortcut::DebugShortcuts );

    QskWindow window;

    CoverflowSimpleExample example;

//    window.addItem( &example );

//    window.resize( 600, 600 );
    example.show();

    return app.exec();
}
