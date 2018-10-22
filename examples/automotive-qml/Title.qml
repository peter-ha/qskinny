import QtQuick 2.11

Item {
    id: root
    property string text

    Row {
        id: row
        spacing: 10
        Rectangle {
            id: leftLine
            height: 2
            width: 0.04 * root.width
            anchors.verticalCenter: text.verticalCenter
            color: "turquoise" // ###
        }
        MainText {
            id: text
            text: root.text
        }
        Rectangle {
            height: 2
            width: root.width - (leftLine.width + text.implicitWidth + 2 * row.spacing)
            anchors.verticalCenter: text.verticalCenter
            color: "turquoise"
        }
    }
}
