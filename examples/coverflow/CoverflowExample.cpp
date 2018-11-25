/******************************************************************************
 * QSkinny - Copyright (C) 2018 Peter Hartmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "CoverflowExample.h"
#include "Coverflow.h"

#include <QImage>

#include <QskGraphic.h>
#include <QskGraphicLabel.h>
#include <QskLinearBox.h>
#include <QskPushButton.h>

CoverflowExample::CoverflowExample()
{
    setPreferredSize( { 800, 400 } );

    const QImage image1( QStringLiteral( ":/images/1.jpg" ) );
    const QImage image2( QStringLiteral( ":/images/2.jpg" ) );
    const QImage image3( QStringLiteral( ":/images/3.jpg" ) );
    const QImage image4( QStringLiteral( ":/images/4.jpg" ) );
    const QImage image5( QStringLiteral( ":/images/5.jpg" ) );
    const QImage image6( QStringLiteral( ":/images/6.jpg" ) );
    const QImage image7( QStringLiteral( ":/images/7.jpg" ) );

    auto coverflow = new Coverflow( contentItem() );

    auto graphicLabel1 = new QskGraphicLabel( coverflow );
    graphicLabel1->setGraphic( QskGraphic::fromImage( image1 ) ); // ### how to do this in Coverflow.cpp?
    graphicLabel1->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel1 );

    auto graphicLabel2 = new QskGraphicLabel( coverflow );
    graphicLabel2->setGraphic( QskGraphic::fromImage( image2 ) );
    graphicLabel2->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel2 );

    auto graphicLabel3 = new QskGraphicLabel( coverflow );
    graphicLabel3->setGraphic( QskGraphic::fromImage( image3 ) );
    graphicLabel3->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel3 );

    auto graphicLabel4 = new QskGraphicLabel( coverflow );
    graphicLabel4->setGraphic( QskGraphic::fromImage( image4 ) );
    graphicLabel4->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel4 );

    auto graphicLabel5 = new QskGraphicLabel( coverflow );
    graphicLabel5->setGraphic( QskGraphic::fromImage( image5 ) );
    graphicLabel5->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel5 );

    auto graphicLabel6 = new QskGraphicLabel( coverflow );
    graphicLabel6->setGraphic( QskGraphic::fromImage( image6 ) );
    graphicLabel6->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel6 );

    auto graphicLabel7 = new QskGraphicLabel( coverflow );
    graphicLabel7->setGraphic( QskGraphic::fromImage( image7 ) );
    graphicLabel7->setFillMode( QskGraphicLabel::Stretch );
    coverflow->addCover( graphicLabel7 );
}
