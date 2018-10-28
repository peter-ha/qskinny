import QtQuick 2.11
import "imports"

Rectangle {
    property bool isPortrait
    property int w: 50
    property int h: 100
    property string source
    width: isPortrait ? w : h
    height: isPortrait ? h : w
    color: Colors.color1

    Image {
        source: parent.source
        property int padding: 25
        x: parent.isPortrait ? 0 : padding
        y: parent.isPortrait ? padding : 0
        width: parent.isPortrait ? parent.width : parent.width - 2 * padding
        height: parent.isPortrait ? parent.height - 2 * padding : parent.height
        sourceSize.width: width
        sourceSize.height: height
    }
}
