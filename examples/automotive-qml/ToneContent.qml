import QtQuick 2.11
import QtQuick.Layouts 1.11

GridLayout {
    rows: 5
    columns: 3
    rowSpacing: 5
    columnSpacing: 20
    MainText {
        id: bassText
        Layout.alignment: Qt.AlignHCenter
        text: "Bass"
    }
    MainText {
        text: "Treble"
        Layout.alignment: Qt.AlignHCenter
    }
    MainText {
        text: "Sub"
        Layout.alignment: Qt.AlignHCenter
    }
    MainText {
        id: bassValue
        text: Number(bassSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
        Layout.alignment: Qt.AlignHCenter
    }
    MainText {
        text: Number(trebleSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
        Layout.alignment: Qt.AlignHCenter
    }
    MainText {
        text: Number(subSlider.value).toLocaleString(Qt.locale("en_EN"), "f", 1)
        Layout.alignment: Qt.AlignHCenter
    }
    ToneButton {
        id: bassPlusButton
        Layout.preferredHeight: width
        text: "+"
        Layout.alignment: Qt.AlignHCenter
        onClicked: bassSlider.value += 2
    }
    ToneButton {
        text: "+"
        Layout.preferredHeight: width
        Layout.alignment: Qt.AlignHCenter
        onClicked: trebleSlider.value += 2
    }
    ToneButton {
        text: "+"
        Layout.preferredHeight: width
        Layout.alignment: Qt.AlignHCenter
        onClicked: subSlider.value += 2
    }
    SoundControlSlider {
        id: bassSlider
        Layout.preferredHeight: parent.height - (bassText.height + bassValue.height + bassPlusButton.height + bassMinusButton.height + parent.rowSpacing * 4)
        Layout.alignment: Qt.AlignHCenter
        value: 30
    }
    SoundControlSlider {
        id: trebleSlider
        Layout.preferredHeight: bassSlider.Layout.preferredHeight
        Layout.alignment: Qt.AlignHCenter
        value: 11
    }
    SoundControlSlider {
        id: subSlider
        Layout.preferredHeight: bassSlider.Layout.preferredHeight
        Layout.alignment: Qt.AlignHCenter
        value: 18
    }
    ToneButton {
        id: bassMinusButton
        Layout.preferredHeight: width
        text: "-"
        Layout.alignment: Qt.AlignHCenter
        onClicked: bassSlider.value -= 2
    }
    ToneButton {
        Layout.preferredHeight: width
        text: "-"
        Layout.alignment: Qt.AlignHCenter
        onClicked: trebleSlider.value -= 2
    }
    ToneButton {
        Layout.preferredHeight: width
        text: "-"
        Layout.alignment: Qt.AlignHCenter
        onClicked: subSlider.value -= 2
    }
}
