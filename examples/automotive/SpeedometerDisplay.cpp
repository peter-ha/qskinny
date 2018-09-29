#include "SpeedometerDisplay.h"

#include "Speedometer.h"
#include "ShaderEffect.h"

#include <QskEvent.h>
#include <QskLinearBox.h>
#include <QskTextLabel.h>

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

    m_revCounterText->setMargins( 50 );
    m_speedometerText->setMargins( 50 );
    m_fuelGaugeText->setMargins( 50 );

    m_fuelGauge->setObjectName( QStringLiteral( "Fuel Gauge" ) );
    m_fuelGauge->setMinimum( 195 );
    m_fuelGauge->setMaximum( 345 );
    m_fuelGauge->setValue( 330 );

    QVector< QString > fuelGaugeLabels;
    fuelGaugeLabels.append( { "0", "", "1/2", "", "1/1" } );
    m_fuelGauge->setLabels( fuelGaugeLabels );

//    m_fuelGauge->setOpacity( 0.3 );

    auto verticalBlur = new ShaderEffect( m_fuelGauge );
    verticalBlur->setProperty( "delta", QSizeF( 0.0, 0.00125 ) ); // ### set depending on height

    verticalBlur->setVertexShader( "" ); // otherwise status will be reported as error
    verticalBlur->setFragmentShader(
        "uniform lowp float qt_Opacity;\n"
        "uniform sampler2D source;\n"
        "uniform highp vec2 delta;\n"
        "\n"
        "varying highp vec2 qt_TexCoord0;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor =(0.0538 * texture2D(source, qt_TexCoord0 - 3.182 * delta)\n"
        "                 + 0.3229 * texture2D(source, qt_TexCoord0 - 1.364 * delta)\n"
        "                 + 0.2466 * texture2D(source, qt_TexCoord0)\n"
        "                 + 0.3229 * texture2D(source, qt_TexCoord0 + 1.364 * delta)\n"
        "                 + 0.0538 * texture2D(source, qt_TexCoord0 + 3.182 * delta)) * qt_Opacity;\n"
        "}\n"
    );

    auto horizontalBlur = new ShaderEffect( verticalBlur );
    horizontalBlur->setProperty( "delta", QSizeF( 0.00125, 0.0 ) ); // ### set depending on width
    horizontalBlur->setVertexShader( verticalBlur->vertexShader() );
    horizontalBlur->setFragmentShader( verticalBlur->fragmentShader() );
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
