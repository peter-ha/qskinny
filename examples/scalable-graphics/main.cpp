/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskGraphic.h>
#include <QskGraphicIO.h>
#include <QskGraphicLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto horizontalBox = new QskLinearBox( Qt::Horizontal );
    horizontalBox->setMargins( 10 );
    horizontalBox->setSpacing( 10 );
    horizontalBox->setPreferredSize( { 200, 75 } );

    QskGraphic graphic1 = QskGraphicIO::read( QStringLiteral( ":/qvg/cloud.qvg" ) );
    auto* label1 = new QskGraphicLabel( graphic1, horizontalBox );
    label1->setAlignment( Qt::AlignCenter );
    label1->setMargins( 10 );
    label1->setBackgroundColor( Qt::magenta );

    QskGraphic graphic2 = QskGraphicIO::read( QStringLiteral( ":/qvg/train.qvg" ) );
    auto* label2 = new QskGraphicLabel( graphic2, horizontalBox );
    label2->setAlignment( Qt::AlignCenter );
    label2->setMargins( 10 );
    label2->setBackgroundColor( Qt::magenta );

    QskWindow window;
    window.addItem( horizontalBox );
    window.show();

    return app.exec();
}
