import QtQuick 2.11
import QtQuick.Controls 2.4
import "imports"

Button {
    id: root
    property bool isPortrait
    property int w: 50
    property int h: 100
    property string source

    background: Rectangle {
        implicitWidth: root.isPortrait ? root.w : root.h
        implicitHeight: root.isPortrait ? root.h : root.w
        color: parent.pressed ? Colors.color2 : Colors.color1

        Image {
            source: root.source
            property int padding: 25
            x: root.isPortrait ? 0 : padding
            y: root.isPortrait ? padding : 0
            width: root.isPortrait ? parent.width : parent.width - 2 * padding
            height: root.isPortrait ? parent.height - 2 * padding : parent.height
            sourceSize.width: width
            sourceSize.height: height
        }
    }
}
