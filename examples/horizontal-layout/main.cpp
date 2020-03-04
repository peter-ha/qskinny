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

    auto* label1 = new QskTextLabel( "control 1" );
    label1->setMargins( 10 );
    label1->setBackgroundColor( Qt::magenta );
    horizontalBox->addItem( label1 );

    auto* label2 = new QskTextLabel( "control 2" );
    label2->setMargins( 10 );
    label2->setBackgroundColor( Qt::magenta );
    horizontalBox->addItem( label2 );

    auto* label3 = new QskTextLabel( "control 3" );
    label3->setMargins( 10 );
    label3->setBackgroundColor( Qt::magenta );
    horizontalBox->addItem( label3 );

    QskWindow window;
    window.addItem( horizontalBox );
    window.show();

    return app.exec();
}
