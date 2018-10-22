import QtQuick 2.11

Rectangle {
    color: "#88000000"
    height: 56
    ButtonBar {
        id: leftButtonBar
        width: 135 // ### do not hardcode width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 15 // ### can we do this in the button bar itself?
        anchors.topMargin: 15
        anchors.rightMargin: 20
        anchors.bottomMargin: 15
        model: [ "bluetooth", "location", "phone" ]
    }
    Text {
        id: date
        anchors.left: leftButtonBar.right
        anchors.verticalCenter: parent.verticalCenter
        text: new Date().toLocaleDateString(Qt.locale("de_DE"), "ddd M dd yyyy")
        font.pixelSize: 20
        color: "white"
    }
    ButtonBar {
        height: parent.height
        width: 120 // ###
        id: rightButtonBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.topMargin: 15
        anchors.rightMargin: 20
        anchors.bottomMargin: 15
        model: [ "user", "bookmark", "menu" ]
    }
}
