/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskBox.h>
#include <QskBoxBorderColors.h>
#include <QskStackBox.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

#define FAKEBOX 0

class FakeStackBox : public QskBox {
public:
    FakeStackBox( QQuickItem* parent = nullptr ) : QskBox( parent )
    {
    }

    void addItem( QQuickItem* item )
    {
        item->setParent( this );
        item->setParentItem( this );
    }

    void setCurrentIndex( int /*index*/ )
    {
        // do nothing
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

#if FAKEBOX
    auto* stackBox = new FakeStackBox();
    stackBox->setMargins( 0 );
    stackBox->setAutoLayoutChildren( true );
    stackBox->setFixedSize( { 100, 80 } ); // ### hack
    stackBox->setGradientHint( QskBox::Panel | QskAspect::Color, { Qt::transparent } );
    stackBox->setBoxBorderColorsHint( QskBox::Panel, { Qt::transparent } );
#else
    auto* stackBox = new QskStackBox;
#endif

    auto* label1 = new QskTextLabel( "control 1" );
    label1->setMargins( 10 );
    label1->setObjectName( "1" );
    label1->setBackgroundColor( Qt::blue );
    stackBox->addItem( label1 );

    auto* label2 = new QskTextLabel( "control 2" );
    label2->setMargins( 10 );
    label2->setObjectName( "2" );
    label2->setBackgroundColor( Qt::cyan );
    stackBox->addItem( label2 );

    auto* label3 = new QskTextLabel( "control 3" );
    label3->setMargins( 10 );
    label3->setObjectName( "3" );
    label3->setBackgroundColor( Qt::magenta );
    stackBox->addItem( label3 );

    stackBox->setCurrentIndex( 2 );

    QskWindow window;
    window.addItem( stackBox );
    window.show();

    return app.exec();
}
