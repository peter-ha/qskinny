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

    auto* label1 = new QskTextLabel( "control 1" );
    label1->setMargins( 10 );
    label1->setBackgroundColor( Qt::magenta );

    // Toggle this for different size hints:
//    label1->setExplicitSizeHint( Qt::PreferredSize, { 150, 60 } );

    qDebug() << "size hint:" << label1->sizeHint() << ", the margins hereby are:" << label1->margins();

    QskWindow window;
    window.addItem( label1 );
    window.show();

    return app.exec();
}
