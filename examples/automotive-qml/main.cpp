#include <QElapsedTimer>
#include <QtGui>
#include <QtQuick>

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
        qDebug() << "memory usage" << checkpointName << ":";
        QProcess::execute( "/bin/bash", { "-c", QString::fromLatin1( "grep '^Rss:' /proc/%1/smaps|grep -o '[0-9]*'|datamash sum 1" ).arg( QCoreApplication::applicationPid() ) } );
#endif
    }
}

int main(int argc, char *argv[])
{
#ifdef Q_TIMER
    s_timer.start();
#endif

    measureMemoryUsage( "before creating QGuiApplication" );
    measureStartupTime( "before creating QGuiApplication" );
    QGuiApplication app(argc, argv);
    measureStartupTime( "after creating QGuiApplication" );
    measureMemoryUsage( "after creating QGuiApplication" );

    QQuickView *view = new QQuickView;
    measureStartupTime( "after creating QQuickView" );
    measureMemoryUsage( "after creating QQuickView" );
    QObject::connect( view->engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit );
#ifdef Q_TIMER
    QObject::connect( view, &QQuickWindow::frameSwapped, []() {
        if( s_timer.isValid() )
        {
            measureStartupTime("after first frame swapped" );
            measureMemoryUsage( "after first frame swapped" );
            s_timer.invalidate();
        }
    });
#endif
    view->setSource( QUrl::fromEncoded( "/home/peter/dev/qskinny/examples/automotive-qml/main.qml" ) );
    view->show();
    measureStartupTime( "after loading QML content" );
    measureMemoryUsage( "after loading QML content" );
    return app.exec();
}
