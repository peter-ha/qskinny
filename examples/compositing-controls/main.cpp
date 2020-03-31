/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <SkinnyFont.h>
#include <SkinnyShortcut.h>

#include <QskLinearBox.h>
#include <QskGraphic.h>
#include <QskGraphicLabel.h>
#include <QskGraphicIO.h>
#include <QskTextLabel.h>
#include <QskWindow.h>

#include <QGuiApplication>

class TextAndGraphic : public QskLinearBox
{

    Q_OBJECT

public:
    TextAndGraphic( const QString& text, const QString& graphicName, QQuickItem* parent = nullptr )
        : QskLinearBox( Qt::Horizontal, parent ),
          m_textLabel( new QskTextLabel( text, this ) )
    {
        setBackgroundColor( Qt::magenta );
        setMargins( 10 );
        setSpacing( 10 );

        addItem( m_textLabel );

        QImage image( QString( ":/images/%1.svg" ).arg( graphicName ) );
        auto graphic = QskGraphic::fromImage( image );
        m_graphicLabel = new QskGraphicLabel( graphic, this );
        m_graphicLabel->setExplicitSizeHint( Qt::PreferredSize, { 30, 30 } );
        addItem( m_graphicLabel );

        setAutoLayoutChildren( true );
    }

private:
    QskTextLabel* m_textLabel;
    QskGraphicLabel* m_graphicLabel;
};

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );
    SkinnyShortcut::enable( SkinnyShortcut::AllShortcuts );

    auto* textAndGraphic = new TextAndGraphic( "Text", "cloud" );

    QskWindow window;
    window.addItem( textAndGraphic );
    window.show();

    return app.exec();
}

#include "main.moc"
