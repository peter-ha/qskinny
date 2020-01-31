/******************************************************************************
 * QSkinny - Copyright (C) 2020 Edelhirsch Software GmbH
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef MATERIAL_GALLERY_H
#define MATERIAL_GALLERY_H

#include <QskGridBox.h>

class MaterialGallery : public QskGridBox
{
    Q_OBJECT

  public:
    MaterialGallery( QQuickItem* parent = nullptr );

};

#endif
