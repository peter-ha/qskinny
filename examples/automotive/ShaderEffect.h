#ifndef SHADEREFFECT_H
#define SHADEREFFECT_H

#include <private/qquickshadereffect_p.h>

#include <memory>

class QQuickShaderEffectSource;

class ShaderEffect : public QQuickShaderEffect
{
    using Inherited = QQuickShaderEffect;

public:
    ShaderEffect( QQuickItem* parent );

private:
    std::unique_ptr< QQuickShaderEffectSource > m_shaderEffectSource;
};

#endif // SHADEREFFECT_H
