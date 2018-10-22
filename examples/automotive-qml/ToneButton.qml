import QtQuick 2.11
import QtQuick.Controls 2.4 // ### is there a newer version?

Button {
    id: root
    width: 30
    height: width
    contentItem: Text {
        color: "turquoise"
        text: parent.text
        font.pixelSize: 35
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        color: parent.pressed ? "#FF0022" : "#011627"
    }
}
