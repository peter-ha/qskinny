import QtQuick 2.11

Grid {
    rows: 5
    columns: 3
    rowSpacing: 5
    columnSpacing: 20
    leftPadding: 20
    rightPadding: 20
    horizontalItemAlignment: Grid.AlignHCenter
    property real contentWidth: width - (leftPadding + columnSpacing * (columns - 1) + rightPadding)
    MainText {
        text: "Bass"
    }
    MainText {
        text: "Treble"
    }
    MainText {
        text: "Sub"
    }
    MainText {
        text: Number(bassSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
    }
    MainText {
        text: Number(trebleSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
    }
    MainText {
        text: Number(subSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
    }
    ToneButton {
        text: "+"
        onClicked: bassSlider.value += 2
    }
    ToneButton {
        text: "+"
        onClicked: trebleSlider.value += 2
    }
    ToneButton {
        text: "+"
        onClicked: subSlider.value += 2
    }
    SoundControlSlider {
        id: bassSlider
        width: 0.33 * parent.contentWidth
        height: 245 // ###
        value: 30
    }
    SoundControlSlider {
        id: trebleSlider
        width: 0.33 * parent.contentWidth
        height: bassSlider.height
        value: 11
    }
    SoundControlSlider {
        id: subSlider
        width: 0.33 * parent.contentWidth
        height: bassSlider.height
        value: 18
    }
    ToneButton {
        text: "-"
        onClicked: bassSlider.value -= 2
    }
    ToneButton {
        text: "-"
        onClicked: trebleSlider.value -= 2
    }
    ToneButton {
        text: "-"
        onClicked: subSlider.value -= 2
    }
}
