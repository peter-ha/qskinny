import QtQuick 2.11
import "imports"

Rectangle {
    color: Colors.darkerBackground
    height: 56
    ButtonBar {
        id: buttonBar
        width: 135 // ### do not hardcode width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 15 // ### can we do this in the button bar itself?
        anchors.topMargin: 15
        anchors.rightMargin: 20
        anchors.bottomMargin: 15
        model: [ "cloud", "man", "bus", "plane", "train" ]
    }
}
