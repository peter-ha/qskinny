import QtQuick 2.11

Grid {
    id: root
    columns: 2
    rows: 2
    columnSpacing: 60
    rowSpacing: 10

    leftPadding: 40
    topPadding: 30
    rightPadding: 40
    bottomPadding: 20
    property real contentWidth: width - (leftPadding + columnSpacing  * (columns - 1) + rightPadding)

    Title {
        id: toneTitle
        height: 30
        width: 0.3 * root.contentWidth
        text: "Tone"
    }
    Title {
        id: balanceFadeTitle
        height: toneTitle.height
        width: 0.7 * root.contentWidth
        text: "Balance / Fade"
    }
    ToneContent {
        width: toneTitle.width
    }
    BalanceFadeContent {
        width: balanceFadeTitle.width
        height: 30
    }
}
