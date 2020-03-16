#ifndef QSKSHADEREFFECTSKINLET_H
#define QSKSHADEREFFECTSKINLET_H

#include "QskSkinlet.h"

class QskShaderEffect;

class QskShaderEffectSkinlet : public QskSkinlet
{
    Q_GADGET

    using Inherited = QskSkinlet;

  public:
    enum NodeRole
    {
        PanelRole
    };

    Q_INVOKABLE QskShaderEffectSkinlet( QskSkin* = nullptr );
    ~QskShaderEffectSkinlet() override;

  protected:
    QSGNode* updateSubNode( const QskSkinnable*,
        quint8 nodeRole, QSGNode* ) const override;

  private:
    QSGNode* updateShaderNode( const QskShaderEffect*, QSGNode* ) const;
};

#endif // QSKSHADEREFFECTSKINLET_H
