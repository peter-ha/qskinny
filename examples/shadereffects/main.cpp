/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskLinearBox.h>
#include <QskShaderEffect.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* box = new QskLinearBox( Qt::Horizontal );
    box->setAutoLayoutChildren( true );

    auto* label = new QskTextLabel( "control 1", box );
    label->setMargins( 10 );
    label->setBackgroundColor( Qt::magenta );

    auto* shaderEffect = new QskShaderEffect( box );
    shaderEffect->setMargins( 10 );
    shaderEffect->setSource( label );

    QskWindow window;
    window.addItem( box );
    window.show();

    return app.exec();
}
