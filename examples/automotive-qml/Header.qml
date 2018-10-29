import QtQuick 2.11
import "imports"

Rectangle {
    color: Colors.darkerBackground
    height: leftButtonBar.height
    ButtonBar {
        id: leftButtonBar
        anchors.top: parent.top
        anchors.left: parent.left
        model: [ "bluetooth", "location", "phone" ]
    }
    Text {
        id: date
        anchors.left: leftButtonBar.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: new Date().toLocaleDateString(Qt.locale("de_DE"), "ddd M dd yyyy")
        font.pixelSize: 20
        color: Colors.color4
    }
    ButtonBar {
        id: rightButtonBar
        height: parent.height
        anchors.top: parent.top
        anchors.right: parent.right
        model: [ "user", "bookmark", "menu" ]
    }
}
