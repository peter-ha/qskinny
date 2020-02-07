/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "MaterialGallery.h"

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskSetup.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );
    qskSetup->setSkin( QStringLiteral( "material" ) );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::Quit | SkinnyShortcut::DebugShortcuts );

    auto* gallery = new MaterialGallery();

    QskWindow window;
    window.setTitle( QStringLiteral( "QSkinny Material style" ) );
    window.addItem( gallery );
    window.show();

    return app.exec();
}
