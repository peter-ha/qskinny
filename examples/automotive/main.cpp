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

static QElapsedTimer s_timer;

namespace
{
    void measureStartupTime( const QByteArray &checkpointName )
    {
#ifdef Q_TIMER
        qDebug() << "time elapsed" << checkpointName << " [ms]:" << s_timer.elapsed();
#endif
    }

    void measureMemoryUsage( const QByteArray &checkpointName )
    {
#ifdef Q_MEMORY
        qDebug() << "memory usage" << checkpointName << " [KB]:";
        QProcess::execute( "/bin/bash", { "-c", QString::fromLatin1( "grep '^Rss:' /proc/%1/smaps|grep -o '[0-9]*'|datamash sum 1" ).arg( QCoreApplication::applicationPid() ) } );
#endif
    }
}

using namespace std;

int main( int argc, char** argv )
{
#ifdef Q_TIMER
    s_timer.start();
#endif

    auto skinFactory = new SkinFactory();

    qskSkinManager->setPluginPaths( QStringList() ); // no plugins
    qskSkinManager->registerFactory(
        QStringLiteral( "SampleSkinFactory" ), skinFactory );

    measureMemoryUsage( "before creating QGuiApplication" );
    measureStartupTime( "before creating QGuiApplication" );
    QGuiApplication app( argc, argv );
    measureStartupTime( "after creating QGuiApplication" );
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

    measureStartupTime( "before creating QskWindow" );
    MainWindow mainWindow;
    measureMemoryUsage( "after creating QskWindow" );
    measureStartupTime( "after creating QskWindow" );

#ifdef Q_TIMER
    QObject::connect( &mainWindow, &QQuickWindow::frameSwapped, []() {
        if( s_timer.isValid() )
        {
            measureStartupTime("after first frame swapped" );
            measureMemoryUsage( "after first frame swapped" );
            s_timer.invalidate();
        }
    });
#endif

    mainWindow.show();

    return app.exec();
}
