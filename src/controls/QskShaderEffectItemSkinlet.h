#ifndef QSKSHADEREFFECTITEMSKINLET_H
#define QSKSHADEREFFECTITEMSKINLET_H

#include "QskSkinlet.h"

class QskShaderEffectItemSkinlet : public QskSkinlet
{
    Q_GADGET

    using Inherited = QskSkinlet;

public:
    QskShaderEffectItemSkinlet( QskSkin* = nullptr );
    ~QskShaderEffectItemSkinlet() override;
};

#endif // QSKSHADEREFFECTITEMSKINLET_H
