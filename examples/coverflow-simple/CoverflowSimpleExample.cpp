/******************************************************************************
 * QSkinny - Copyright (C) 2018 Peter Hartmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "CoverflowSimpleExample.h"
#include "SimpleFlowView.h"

#include <QImage>

#include <QskGraphic.h>
#include <QskGraphicLabel.h>
#include <QskLinearBox.h>
#include <QskPushButton.h>

CoverflowSimpleExample::CoverflowSimpleExample()
{
    setPreferredSize( { 800, 400 } );

    auto coverflow = new SimpleFlowView( contentItem() );
    coverflow->setCount( 7 );
    coverflow->setCurrentIndex( 2 );
}
