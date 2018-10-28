import QtQuick 2.11
import QtQuick.Controls 2.4
import "imports"

Button {
    id: root
    width: 30
    height: width
    contentItem: Text {
        color: Colors.color3
        text: parent.text
        font.pixelSize: 35
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        color: parent.pressed ? Colors.color2 : Colors.color1
    }
}
