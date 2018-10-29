import QtQuick 2.11
import "imports"

Rectangle {
    color: Colors.darkerBackground
    height: buttonBar.height

    ButtonBar {
        id: buttonBar
        anchors.top: parent.top
        anchors.left: parent.left
        model: [ "cloud", "man", "bus", "plane", "train" ]
    }
}
