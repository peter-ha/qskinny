/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto horizontalBox = new QskLinearBox( Qt::Horizontal );
    horizontalBox->setDefaultAlignment( Qt::AlignLeft );
    horizontalBox->setMargins( 10 );
    horizontalBox->setSpacing( 10 );

    auto* label1 = new QskTextLabel( "stretch factor 1" );
    label1->setMargins( 10 );
    label1->setBackgroundColor( Qt::magenta );
    horizontalBox->addItem( label1 );
    horizontalBox->setStretchFactor( label1, 1 );

    auto* label2 = new QskTextLabel( "stretch factor 2" );
    label2->setMargins( 10 );
    label2->setBackgroundColor( Qt::magenta );
    horizontalBox->addItem( label2 );
    horizontalBox->setStretchFactor( label2, 2 );

    QskWindow window;
    window.addItem( horizontalBox );
    window.show();

    return app.exec();
}
