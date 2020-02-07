/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "MaterialGallery.h"

#include <QskBoxBorderMetrics.h>
#include <QskGraphic.h>
#include <QskGraphicIO.h>
#include <QskGridBox.h>
#include <QskPushButton.h>

#include <QImage>

MaterialGallery::MaterialGallery( QQuickItem* parent ) : QskGridBox( parent )
{
    setMargins( 30 );
    setSpacing( 30 );

    auto containedButton = new QskPushButton( "Contained button", this );
    containedButton->setSizePolicy( Qt::Horizontal, QskSizePolicy::Maximum );
    addItem( containedButton, 0, 0 );

    auto outlinedButton = new QskPushButton( "Outlined button", this );
    outlinedButton->setFlat( true );
    // ### there should be a nicer way to make an outlined button:
    outlinedButton->setBoxBorderMetricsHint( QskPushButton::Panel, 1 );
    addItem( outlinedButton, 0, 1 );

    auto textButton = new QskPushButton( "Text button", this );
    textButton->setFlat( true );
    addItem( textButton, 0, 2 );

    const auto graphic = QskGraphicIO::read( QStringLiteral( ":/qvg/ic_star_rate_18px.qvg" ) );

    auto containedButtonWithIcon = new QskPushButton( "Contained Button", this );
    containedButtonWithIcon->setGraphic( graphic );
    // The spec actually says 18 pixels for the icon, but 17 resembles more closely what is rendered
    containedButtonWithIcon->setGraphicSourceSize( { 18, 18 } ); // ### we should do that in the skin
    addItem( containedButtonWithIcon, 1, 0 );

    auto outlinedButtonWithIcon = new QskPushButton( "Outlined Button", this );
    outlinedButtonWithIcon->setFlat( true );
    outlinedButtonWithIcon->setGraphic( graphic );
    outlinedButtonWithIcon->setGraphicSourceSize( { 18, 18 } );
    outlinedButtonWithIcon->setBoxBorderMetricsHint( QskPushButton::Panel, 1 );
    addItem( outlinedButtonWithIcon, 1, 1 );

    auto textButtonWithIcon = new QskPushButton( "Text button", this );
    textButtonWithIcon->setFlat( true );
    textButtonWithIcon->setGraphic( graphic );
    textButtonWithIcon->setGraphicSourceSize( { 18, 18 } );
    addItem( textButtonWithIcon, 1, 2 );
}
