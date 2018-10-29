import QtQuick 2.11

Item {
    id: root
    anchors.leftMargin: 15
    anchors.topMargin: 15
    anchors.rightMargin: 20
    anchors.bottomMargin: 15
    width: row.width
    height: row.height + anchors.topMargin + anchors.bottomMargin
    property var model

    Row {
        id: row
        spacing: 20

        Repeater {
            model: root.model
            delegate:  Image {
                source: "/../automotive/images/" + modelData + ".svg"
                width: 25
                height: 25
                sourceSize.width: width
                sourceSize.height: height
            }
        }
    }
}
