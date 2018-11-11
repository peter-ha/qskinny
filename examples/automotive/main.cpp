#include "MainWindow.h"
#include "SkinFactory.h"

#include <QskSetup.h>
#include <QskShortcutMap.h>
#include <QskSkinManager.h>
#include <SkinnyShortcut.h>

#include <QElapsedTimer>
#include <QGuiApplication>
#include <QProcess>

#include <iostream>

#define Q_TIMER 1
#define Q_MEMORY 1

namespace
{
    void measureMemoryUsage( const QByteArray &checkpointName )
    {
#ifdef Q_MEMORY
        qDebug() << "memory usage" << checkpointName << ":";
        QProcess::execute( "/bin/bash", { "-c", QString::fromLatin1( "grep '^Rss:' /proc/%1/smaps|grep -o '[0-9]*'|datamash sum 1" ).arg( QCoreApplication::applicationPid() ) } );
#endif
    }
}

using namespace std;

int main( int argc, char** argv )
{
#ifdef Q_TIMER
    QElapsedTimer timer;
    timer.start();
#endif

    auto skinFactory = new SkinFactory();

    qskSkinManager->setPluginPaths( QStringList() ); // no plugins
    qskSkinManager->registerFactory(
        QStringLiteral( "SampleSkinFactory" ), skinFactory );

    measureMemoryUsage( "before creating QGuiApplication" );
    QGuiApplication app( argc, argv );
    measureMemoryUsage( "after creating QGuiApplication" );

    /*
        When going over QPainter for the SVGs we prefer the raster paint
        engine, simply showing better results. Interestingly the OpenGL paint
        engine was even slower for the use case of non-complex SVGs.
        Looks like its tesselation is not much faster than "pixeling"
        those images directly.
     */
    qskSetup->setControlFlag( QskSetup::PreferRasterForTextures, true );

    // Starting with a simple skin  made for this example
    // CTRL-S allow to rotate through the registered skins and CTRL-T
    // changes the colors, when the DefaultSkin is active.

    qskSetup->setSkin( QStringLiteral( "DefaultSkin" ) );

    cout << "CTRL-S to change the skin." << endl;
    cout << "CTRL-T to change the color scheme, when the \"Default\" skin is active." << endl;

    QskShortcutMap::addShortcut( QKeySequence( Qt::CTRL + Qt::Key_T ),
        false, skinFactory, SLOT(toggleScheme()) );

    QskShortcutMap::addShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ),
        false, skinFactory, SLOT(rotateSkin()) );

    // With CTRL-B you can rotate a couple of visual debug modes
    SkinnyShortcut::enable( SkinnyShortcut::DebugBackground |
        SkinnyShortcut::DebugStatistics | SkinnyShortcut::Quit );

    MainWindow mainWindow;
    measureMemoryUsage( "after creating QskWindow" );

#ifdef Q_TIMER
    QObject::connect( &mainWindow, &QQuickWindow::frameSwapped, [ &timer ]() {
        if( timer.isValid() )
        {
            measureMemoryUsage( "after first frame swapped" );
            qDebug() << "first frame swap after" << timer.elapsed() << "ms";
            timer.invalidate();
        }
    });
#endif

    mainWindow.show();

    return app.exec();
}
