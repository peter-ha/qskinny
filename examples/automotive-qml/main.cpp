#include <QElapsedTimer>
#include <QtGui>
#include <QtQuick>

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

int main(int argc, char *argv[])
{
#ifdef Q_TIMER
    QElapsedTimer timer;
    timer.start();
#endif

    measureMemoryUsage( "before creating QGuiApplication" );
    QGuiApplication app(argc, argv);
    measureMemoryUsage( "after creating QGuiApplication" );

    QQuickView *view = new QQuickView;
    measureMemoryUsage( "after creating QQuickView" );
    QObject::connect( view->engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit );
#ifdef Q_TIMER
    QObject::connect( view, &QQuickWindow::frameSwapped, [ &timer ]() {
        if( timer.isValid() )
        {
            measureMemoryUsage( "after first frame swapped" );
            qDebug() << "first frame swap after" << timer.elapsed() << "ms";
            timer.invalidate();
        }
    });
#endif
    view->setSource( QUrl::fromEncoded( "/home/peter/dev/qskinny/examples/automotive-qml/main.qml" ) );
    view->show();
    measureMemoryUsage( "after loading QML content" );
    return app.exec();
}
