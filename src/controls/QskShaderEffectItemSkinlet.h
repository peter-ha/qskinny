#ifndef QSKSHADEREFFECTITEMSKINLET_H
#define QSKSHADEREFFECTITEMSKINLET_H

#include "QskSkinlet.h"

class QskShaderEffectItem;

class QskShaderEffectItemSkinlet : public QskSkinlet
{
    Q_GADGET

    using Inherited = QskSkinlet;

public:
    enum NodeRole
    {
        ShaderRole
    };

    Q_INVOKABLE QskShaderEffectItemSkinlet( QskSkin* = nullptr );
    ~QskShaderEffectItemSkinlet() override;

    QRectF subControlRect( const QskSkinnable*, QskAspect::Subcontrol ) const override;

protected:
    QSGNode* updateSubNode( const QskSkinnable*, quint8 nodeRole, QSGNode* ) const override;

private:
    QSGNode* updateShaderNode( const QskShaderEffectItem*, QSGNode* ) const;
};

#endif // QSKSHADEREFFECTITEMSKINLET_H
