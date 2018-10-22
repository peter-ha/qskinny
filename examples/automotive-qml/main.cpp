#include <QElapsedTimer>
#include <QtGui>
#include <QtQuick>


int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();
    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    QObject::connect( view->engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit );
    QObject::connect( view, &QQuickWindow::frameSwapped, [ &timer ]() {
        if( timer.isValid() )
        {
            qDebug() << "first frame swap after" << timer.elapsed() << "ms";
            timer.invalidate();
        }
    });
    view->setSource( QUrl::fromEncoded( "qrc:///main.qml" ) );
    view->show();
    return app.exec();
}
