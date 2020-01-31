/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "MaterialGallery.h"

#include <QskBoxBorderMetrics.h>
#include <QskGridBox.h>
#include <QskPushButton.h>

MaterialGallery::MaterialGallery( QQuickItem* parent ) : QskGridBox( parent )
{
    setMargins( 30 );
    setSpacing( 30 );

    auto containedButton = new QskPushButton( "Contained Button", this );
    addItem( containedButton, 0, 0 );

    auto outlinedButton = new QskPushButton( "Outlined Button", this );
    outlinedButton->setFlat( true );
    // ### there should be a nicer way to make an outlined button:
    outlinedButton->setBoxBorderMetricsHint( QskPushButton::Panel, 1 );
    addItem( outlinedButton, 0, 1 );

    auto textButton = new QskPushButton( "Text Button", this );
    textButton->setFlat( true );
    addItem( textButton, 0, 2 );
}
