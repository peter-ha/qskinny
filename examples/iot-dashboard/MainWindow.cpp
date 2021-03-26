#include "MainWindow.h"

#include "MainContent.h"
#include "MenuBar.h"

#include <QskLinearBox.h>

MainWindow::MainWindow()
    : QskWindow()
    , m_mainLayout( new QskLinearBox( Qt::Horizontal, contentItem() ) )
    , m_menuBar( new MenuBar( m_mainLayout ) )
    , m_mainContent( new MainContent( m_mainLayout ) )
{
    setPreferredSize( { 1024, 600 } );
    setTitle( "IOT dashboard" );
}
