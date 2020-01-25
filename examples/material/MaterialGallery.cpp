/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "MaterialGallery.h"

#include <QskGridBox.h>
#include <QskPushButton.h>

MaterialGallery::MaterialGallery( QQuickItem* parent ) : QskControl( parent )
{
    qDebug() << Q_FUNC_INFO;

    auto box = new QskGridBox( this );

    auto containedButton = new QskPushButton( "Contained Button", box );

    box->addItem( containedButton, 0, 0 );

    //setAutoFillBackground(true);
    //setBackground(Qt::red);
}
