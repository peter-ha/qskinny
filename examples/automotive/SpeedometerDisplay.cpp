#include "SpeedometerDisplay.h"

#include "Speedometer.h"

#include <QskEvent.h>
#include <QskLinearBox.h>
#include <QskTextLabel.h>

#include <private/qquickshadereffect_p.h>
#include <QTime>
#include <QTimer>
#include <QtGlobal>

SpeedometerDisplay::SpeedometerDisplay( QQuickItem* parent )
    : QskControl( parent )
    , m_box( new QskLinearBox( Qt::Horizontal, this ) )
    , m_revCounter( new Speedometer( m_box ) )
    , m_revCounterText( new QskTextLabel( QStringLiteral( "x 1000 min^-1" ), m_revCounter ) )
    , m_speedometer( new Speedometer( m_box ) )
    , m_speedometerText( new QskTextLabel( QStringLiteral( "km/h" ), m_speedometer ) )
    , m_fuelGauge( new Speedometer( m_box ) )
    , m_fuelGaugeText( new QskTextLabel( QStringLiteral( "fuel" ), m_fuelGauge ) )
{
    qsrand( static_cast< uint >( QTime::currentTime().msec() ) );

    setPolishOnResize( true );

    m_box->setAutoAddChildren( true );
    m_box->setAutoLayoutChildren( true );
    m_box->setSpacing( 20 );

    m_revCounter->setObjectName( QStringLiteral( "RevCounter" ) );
    m_revCounter->setMinimum( 145 );
    m_revCounter->setMaximum( 305 );
    m_revCounter->setValue( 200 );
    QVector< QString > revCounterLabels;
    int numberLabels = 8;
    revCounterLabels.reserve( numberLabels );

    for ( int i = 0; i < numberLabels; ++i )
    {
        revCounterLabels.append( QString::number( i ) );
    }

    m_revCounter->setLabels( revCounterLabels );

    m_speedometer->setObjectName( QStringLiteral( "Speedometer" ) );
    m_speedometer->setMinimum( -215 );
    m_speedometer->setMaximum( 35 );
    m_speedometer->setValue( -90 );
    QVector< QString > speedometerLabels;
    numberLabels = 23;
    speedometerLabels.reserve( numberLabels );

    for ( int i = 0; i < numberLabels; ++i )
    {
        speedometerLabels.append( QString::number( i * 10 ) );
    }

    m_speedometer->setLabels( speedometerLabels );

    auto timer = new QTimer( this );

    connect( timer, &QTimer::timeout, this, [ this ]()
    {
        auto speedometerValue = m_speedometer->value() + qrand() % 3 - 0.95;
        m_speedometer->setValue( speedometerValue );

        auto fuelGaugeValue = 0.99997 * m_fuelGauge->value();
        m_fuelGauge->setValue( fuelGaugeValue );
    });

    timer->setInterval( 16 );
    timer->start();


    auto shaderEffect = new QQuickShaderEffect( m_fuelGauge );

    shaderEffect->setVertexShader(
"                attribute highp vec4 qt_Vertex;\n"
"                attribute highp vec2 qt_MultiTexCoord0;\n"
"                uniform highp mat4 qt_Matrix;\n"
"                varying highp vec2 qt_TexCoord0;\n"
"                void main() {\n"
"                    gl_Position = qt_Matrix * qt_Vertex;\n"
"                    qt_TexCoord0 = qt_MultiTexCoord0;\n"
"                }\n"
                );
    shaderEffect->setFragmentShader(
"                uniform highp sampler2D source;\n"
"                uniform lowp float qt_Opacity;\n"
"                uniform mediump float spread;\n"
"                uniform highp vec2 dirstep;\n"
"                uniform lowp vec4 color;\n"
"                uniform lowp float thickness;\n"
"                \n"
"                varying highp vec2 qt_TexCoord0;\n"
"                \n"
"                void main() {\n"
"                    mediump float result = 0.0;\n"
"                    highp vec2 pixelStep = dirstep * spread;\n"
"                    result += float(1) * texture2D(source, qt_TexCoord0 + pixelStep * float(0)).a;\n"
"                    const mediump float wSum = float(1);\n"
"                    gl_FragColor = mix(vec4(0), color, clamp((result / wSum) / thickness, 0.0, 1.0)) * qt_Opacity;\n"
"                }\n"
                );

    QTimer::singleShot( 3000, this, [shaderEffect, this]() {
        qDebug() << "shader status:" << shaderEffect->log() << shaderEffect->status();
    });

    m_fuelGauge->setObjectName( QStringLiteral( "Fuel Gauge" ) );
    m_fuelGauge->setMinimum( 195 );
    m_fuelGauge->setMaximum( 345 );
    m_fuelGauge->setValue( 330 );

    // ### we should introduce a class QskShader and do this in the constructor or so
    if( shaderEffect->parentItem() != nullptr )
    {
        connect( shaderEffect->parentItem(), &QQuickItem::widthChanged, [shaderEffect]()
        {
            shaderEffect->setWidth( shaderEffect->parentItem()->width() );
        });

        connect( shaderEffect->parentItem(), &QQuickItem::heightChanged, [shaderEffect]()
        {
            shaderEffect->setHeight( shaderEffect->parentItem()->height() );
        });
    }

    QVector< QString > fuelGaugeLabels;
    fuelGaugeLabels.append( { "0", "", "1/2", "", "1/1" } );

    m_fuelGauge->setLabels( fuelGaugeLabels );

    m_revCounterText->setMargins( 50 );
    m_speedometerText->setMargins( 50 );
    m_fuelGaugeText->setMargins( 50 );
}

void SpeedometerDisplay::updateLayout()
{
    auto radius = qMin( 0.33 * size().width(), size().height() );
    auto x = ( width() - radius * 2.7 - 2 * m_box->spacing() ) / 2;
    auto y = ( height() - radius ) / 2;
    m_box->setPosition( { x, y } );

    m_revCounter->setFixedSize( radius, radius );
    QSizeF hint = m_revCounterText->sizeHint();
    x = ( radius - hint.width() ) / 2;
    y = ( ( radius - hint.height() ) / 2 ) + m_revCounterText->margins().top();
    m_revCounterText->setGeometry( x, y, hint.width(), hint.height() );

    m_speedometer->setFixedSize( radius, radius );
    hint = m_speedometerText->sizeHint();
    x = ( radius - hint.width() ) / 2;
    y = ( ( radius - hint.height() ) / 2 ) + m_speedometerText->margins().top();
    m_speedometerText->setGeometry( x, y, hint.width(), hint.height() );

    m_fuelGauge->setFixedSize( 0.7 * radius, 0.7 * radius );
    hint = m_fuelGaugeText->sizeHint();
    x = ( 0.7 * radius - hint.width() ) / 2;
    y = ( ( 0.7 * radius - hint.height() ) / 2 ) + m_fuelGaugeText->margins().top();
    m_fuelGaugeText->setGeometry( x, y, hint.width(), hint.height() );
}
