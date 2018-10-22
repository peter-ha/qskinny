import QtQuick 2.11

Item {
    id: root
    property var model
    Row {
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
