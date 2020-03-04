/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskBox.h>
#include <QskBoxBorderColors.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

class FakeStackBox : public QskBox {
public:
    FakeStackBox( QQuickItem* parent = nullptr ) : QskBox( parent )
    {
    }

protected:
    void updateLayout() override
    {
        for ( int a = 0; a < children().count(); a++ )
        {
            auto control = static_cast< QskControl* >( children().at( a ) );

            if ( control->objectName() == "3" )
                control->setPosition( { 20, 20 } );
            else if( control->objectName() == "2" )
                control->setPosition( { 10, 10 } );
            else if( control->objectName() == "1" )
                control->setPosition( { 0, 0 } );
        }
    }
};

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* box = new FakeStackBox();
    box->setMargins( 0 );
    box->setAutoLayoutChildren( true );
    box->setFixedSize( { 100, 80 } ); // ### hack
    box->setGradientHint( QskBox::Panel | QskAspect::Color, { Qt::transparent } );
    box->setBoxBorderColorsHint( QskBox::Panel, { Qt::transparent } );

    auto* label1 = new QskTextLabel( "control 1", box );
    label1->setMargins( 10 );
    label1->setObjectName( "1" );
    label1->setBackgroundColor( Qt::blue );

    auto* label2 = new QskTextLabel( "control 2", box );
    label2->setMargins( 10 );
    label2->setObjectName( "2" );
    label2->setBackgroundColor( Qt::cyan );

    auto* label3 = new QskTextLabel( "control 3", box );
    label3->setMargins( 10 );
    label3->setObjectName( "3" );
    label3->setBackgroundColor( Qt::magenta );

    QskWindow window;
    window.addItem( box );
    window.show();

    return app.exec();
}
