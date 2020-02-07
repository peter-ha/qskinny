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

        QColor baseColor;
        QColor textColor;
    };

    class Editor : private QskSkinHintTableEditor
    {
      public:
        Editor( QskSkinHintTable* table, const ColorPalette& palette )
            : QskSkinHintTableEditor( table )
            , m_pal( palette )
        {
    buttonFont.setPixelSize( 14 );

    // ### We could define some ButtonFont or so
    setFont( QskSkin::MediumFont, buttonFont );
        }

        void setup();

      private:
        void setupControl();
        
        void setupProgressBar();
        void setupTextLabel();

        const ColorPalette& m_pal;
    };
}

void QskMaterialSkin::resetColors( const QColor& /*accent*/ )
{
    m_data->palette.resetColors();

    setupBox();
    setupDialogButtonBox();
    setupDialogButton();
    setupFocusIndicator();
    setupInputPanel();
    setupVirtualKeyboard();
    setupListView();
    setupPageIndicator();
    setupPopup();
    setupProgressBar();
    setupPushButton();
    setupScrollView();
    setupSeparator();
    setupSlider();
    setupSubWindow();
    setupTabButton();
    setupTabBar();
    setupTabView();
    setupTextLabel();
    setupTextInput();
}

void Editor::setupControl()
{
    using A = QskAspect;
    using Q = QskControl;

    setPadding( A::Control, 4 );

    // ### do we need this?
    setColor( A::Control | A::StyleColor | Q::Disabled,
        qskShadedColor( m_pal.textColor, 0.6 ) );
    using Q = QskProgressBar;
    {
        setMetric( subControl | A::Size, 5 );
        setPadding( subControl, 0 );
        setBoxBorderMetrics( subControl, 0 );
    }

    setGradient( Q::Groove, Grey );
    setMetric( Q::Groove | A::Size, 5 );
    setGradient( Q::Bar, m_pal.accentColor );
}

void Editor::setupFocusIndicator()
{
    using Q = QskFocusIndicator;

    setPadding( Q::Panel, 5 );
        setStrutSize( subControl, extent, extent );
}

void Editor::setupPushButton()
{
    using A = QskAspect;
    using namespace QskRgb;
    using Q = QskPushButton;

    setMetric( Q::Panel | MaximumHeight, qskDpiScaled( 36.0 ) );

    const QskMargins padding( 16, 0 ); // ### vertical padding?

    setMargins( Q::Panel | Padding, padding ); // ### remove, use text and graphics margins instead
//    setMargins( Q::Text | Padding, 16 );

    setGradient( Q::Panel, { "#6200EE" } );
    setGradient( Q::Panel | Q::Flat, Qt::white );

    setColor( Q::Text, m_data->palette.textColor );
    setColor( Q::Text | Q::Flat, m_data->palette.baseColor );
    setFontRole( Q::Text, MediumFont );
    setAlignment( Q::Text, Qt::AlignCenter );
    setBoxShape( Q::Panel, 4 );

    // for outlined buttons:
    setBoxBorderColors(Q::Panel | Q::Flat, { m_data->palette.baseColor } );

    // graphics for buttons:
    setSkinHint( Q::Graphic | Alignment, Qt::AlignLeft );
    setMetric( QskPushButton::Panel | QskAspect::Spacing, 3 );
    setMargins( Q::Graphic | Padding, { 13, 0, 8, 0 } );

    setGraphicRole( Q::Graphic, GraphicRoleContained );
    QskColorFilter containedFilter;
    const auto tc = m_data->palette.textColor;
    containedFilter.addColorSubstitution( Qt::black, qRgb( tc.red(), tc.green(), tc.blue() ) );
    setGraphicFilter( GraphicRoleContained, containedFilter );

    setGraphicRole( Q::Graphic | Q::Flat, GraphicRoleOutlined );
    const auto bc = m_data->palette.baseColor;
    QskColorFilter outlinedFilter;
    outlinedFilter.addColorSubstitution( Qt::black, qRgb( bc.red(), bc.green(), bc.blue() ) );
    setGraphicFilter( GraphicRoleOutlined, outlinedFilter );

    // Pressed / hover states:
    auto pressedColor = m_data->palette.baseColor;
    pressedColor.setAlpha( 100 );
    setGradient( QskPushButton::Panel | QskPushButton::Pressed, pressedColor );
    setGradient( QskPushButton::Panel | Q::Flat | QskPushButton::Pressed, pressedColor );

    auto hoveredContainedColor = m_data->palette.baseColor;
    hoveredContainedColor.setAlpha( 230 );
    setGradient( QskPushButton::Panel | QskPushButton::Hovered, hoveredContainedColor );

    auto hoveredOutlinedColor = m_data->palette.baseColor;
    hoveredOutlinedColor.setAlpha( 20 );
    setGradient( QskPushButton::Panel | Q::Flat | QskPushButton::Hovered, hoveredOutlinedColor );

QskMaterialSkin::~QskMaterialSkin()
{
}

void QskMaterialSkin::resetColors( const QColor& accent )
{
    m_data->palette = ColorPalette( m_data->palette.baseColor,
        accent, m_data->palette.contrastColor );

    Editor editor( &hintTable(), m_data->palette );
    editor.setup();
}

#include "moc_QskMaterialSkin.cpp"
