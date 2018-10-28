import QtQuick 2.11
import QtQuick.Controls 2.4
import "imports"

Slider {
    id: root
    orientation: Qt.Vertical
    from: 0
    to: 40
    background: Rectangle {
        id: bla
        anchors.centerIn: root
        width: 2
        height: root.height
        radius: 2
        color: Colors.color4darker
        Rectangle {
            width: 2
            height: root.visualPosition * parent.height
            color: Colors.color4
            radius: 2
        }
    }
    handle: Rectangle {
        x: root.leftPadding + root.availableWidth / 2 - width / 2
        y: root.topPadding + root.visualPosition * (root.availableHeight - height)
        radius: 10
        implicitWidth: 20
        implicitHeight: 20
        color: Colors.color5
    }
}
