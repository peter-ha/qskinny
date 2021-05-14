/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#include "QskMaterialSkin.h"

#include <QskSkinHintTableEditor.h>

#include <QskProgressBar.h>
#include <QskBoxBorderColors.h>
#include <QskBoxBorderMetrics.h>
#include <QskColorFilter.h>
#include <QskFunctions.h>
#include <QskMargins.h>
#include <QskPushButton.h>
#include <QskRgbValue.h>
#include <QskSkinlet.h>

namespace
{
    class ColorPalette
    {
      public:
        ColorPalette()
        {
            resetColors();
        }

        void resetColors()
        {
            baseColor = "#6200EE";
            textColor = Qt::white;
        }

        QColor baseColor = "#6200EE"; // ### match Material terminology
        QColor textColor = Qt::white;
    };

    class Editor : private QskSkinHintTableEditor
    {
      public:
        Editor( QskSkinHintTable* table, const ColorPalette& palette )
            : QskSkinHintTableEditor( table )
            , m_pal( palette )
        {
        }

        void setup();

      private:
        void setupControl();
        
        void setupPushButton();

        const ColorPalette& m_pal;
    };
}

void Editor::setup()
{
    setupControl();

    setupPushButton();
}

void Editor::setupControl()
{
    using A = QskAspect;
    using Q = QskControl;

    setPadding( A::Control, 4 );

    // ### do we need this?
    auto color = m_pal.textColor;
    color.setAlphaF( 0.6 );
    setColor( A::Control | A::StyleColor | Q::Disabled, color );
}

void Editor::setupPushButton()
{
    using A = QskAspect;
    using namespace QskRgb;
    using Q = QskPushButton;
    using M = QskMaterialSkin;

    // The left padding depends on whether there is an icon or not,
    // so we distribute the pixels to the text, icon and panel:
    setPadding( Q::Panel, {8, 0, 0, 0} );
    setPadding( Q::Text, {8, 0, 0, 0} );

    setGradient( Q::Panel, { "#6200EE" } );
    setGradient( Q::Panel | Q::Flat, Qt::white );

    setColor( Q::Text, m_pal.textColor );
    setColor( Q::Text | Q::Flat, m_pal.baseColor );
    setFontRole( Q::Text, QskSkin::MediumFont );
    setAlignment( Q::Text, Qt::AlignCenter );
    setBoxShape( Q::Panel, 4 );
//    setPadding(Q::Text, 0);
    setSpacing(Q::Panel, 0);

    setStrutSize( Q::Panel, {64, 36} );

    // for outlined buttons:
    setBoxBorderColors(Q::Panel | Q::Flat, { m_pal.baseColor } );

    // graphics for buttons:
    setAlignment( Q::Graphic | A::Alignment, Qt::AlignLeft );
    setPadding(Q::Graphic, 0);
//    setPadding(Q::Graphic, { 13, 0, 8, 0 } );

    setGraphicRole( Q::Graphic, M::GraphicRoleContained );

    setGraphicRole( Q::Graphic | Q::Flat, M::GraphicRoleOutlined );

    // Pressed / hover states:
    auto pressedColor = m_pal.baseColor;
    pressedColor.setAlpha( 100 );
    setGradient( QskPushButton::Panel | QskPushButton::Pressed, pressedColor );
    setGradient( QskPushButton::Panel | Q::Flat | QskPushButton::Pressed, pressedColor );

    auto hoveredContainedColor = m_pal.baseColor;
    hoveredContainedColor.setAlpha( 230 );
    setGradient( QskPushButton::Panel | QskPushButton::Hovered, hoveredContainedColor );

    auto hoveredOutlinedColor = m_pal.baseColor;
    hoveredOutlinedColor.setAlpha( 20 );
    setGradient( QskPushButton::Panel | Q::Flat | QskPushButton::Hovered, hoveredOutlinedColor );
}

class QskMaterialSkin::PrivateData
{
  public:
    ColorPalette palette;
};

QskMaterialSkin::QskMaterialSkin( QObject* parent )
    : Inherited( parent )
    , m_data( new PrivateData() )
{
    setupFonts( "Roboto" );

    auto buttonFont = font( QskSkin::DefaultFont );
    buttonFont.setCapitalization( QFont::AllUppercase );
    buttonFont.setPixelSize( 14 );

    // ### We could define some ButtonFont or so
    setFont( QskSkin::MediumFont, buttonFont );

    Editor editor( &hintTable(), m_data->palette );
    editor.setup();

    QskColorFilter containedFilter;
    const auto tc = m_data->palette.textColor;
    containedFilter.addColorSubstitution( Qt::black, qRgb( tc.red(), tc.green(), tc.blue() ) );
    setGraphicFilter( GraphicRoleContained, containedFilter );

    const auto bc = m_data->palette.baseColor;
    QskColorFilter outlinedFilter;
    outlinedFilter.addColorSubstitution( Qt::black, qRgb( bc.red(), bc.green(), bc.blue() ) );
    setGraphicFilter( GraphicRoleOutlined, outlinedFilter );
}

QskMaterialSkin::~QskMaterialSkin()
{
}

void QskMaterialSkin::resetColors( const QColor& /*accent*/ )
{
    m_data->palette = ColorPalette();

    Editor editor( &hintTable(), m_data->palette );
    editor.setup();
}

#include "moc_QskMaterialSkin.cpp"
