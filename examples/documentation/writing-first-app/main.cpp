#include <SkinnyFont.h>
#include <QskWindow.h>
#include <QskLinearBox.h>
#include <QskPushButton.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    SkinnyFont::init( &app );

    auto* horizontalBox = new QskLinearBox( Qt::Horizontal );
    auto* button1 = new QskPushButton( "button 1", horizontalBox );
    auto* button2 = new QskPushButton( "button 2", horizontalBox );

    QskWindow window;
    window.addItem( horizontalBox );
    window.show();

    return app.exec();
}
