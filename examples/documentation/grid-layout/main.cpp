/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskGridBox.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto gridBox= new QskGridBox();
    gridBox->setDefaultAlignment( Qt::AlignLeft );
    gridBox->setMargins( 10 );
    gridBox->setSpacing( 10 );

    auto* label1 = new QskTextLabel( "control 1" );
    label1->setMargins( 10 );
    label1->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label1, 0, 0 );

    auto* label2 = new QskTextLabel( "control 2" );
    label2->setMargins( 10 );
    label2->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label2, 0, 1 );

    auto* label3 = new QskTextLabel( "control 3" );
    label3->setMargins( 10 );
    label3->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label3, 0, 2 );

    auto* label4 = new QskTextLabel( "control 4" );
    label4->setMargins( 10 );
    label4->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label4, 1, 0, 1, 2 );

    auto* label5 = new QskTextLabel( "control 5" );
    label5->setMargins( 10 );
    label5->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label5, 1, 2, 2, 1 );

    auto* label6 = new QskTextLabel( "control 6" );
    label6->setMargins( 10 );
    label6->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label6, 2, 0 );

    auto* label7 = new QskTextLabel( "control 7" );
    label7->setMargins( 10 );
    label7->setBackgroundColor( Qt::magenta );
    gridBox->addItem( label7, 2, 1, 1, 2 );

    QskWindow window;
    window.addItem( gridBox );
    window.show();

    return app.exec();
}
