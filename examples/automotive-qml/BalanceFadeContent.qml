import QtQuick 2.11
import QtQuick.Layouts 1.11
import "imports"

GridLayout {
    rows: 3
    columns: 3
    rowSpacing: 5
    columnSpacing: 5
    property int step: 5

    BalanceFadeArrow {
        source: "../automotive/images/up.svg"
        Layout.alignment: Qt.AlignHCenter
        isPortrait: false
        Layout.columnSpan: 3
        onClicked: dot.y -= parent.step
    }
    BalanceFadeArrow {
        source: "../automotive/images/left.svg"
        isPortrait: true
        onClicked: dot.x -= parent.step
    }
    Image {
        id: car
        source: "../automotive/images/car.svg"
        height: 260
        sourceSize.width: width
        sourceSize.height: height
        Rectangle { // horizontal line
            width: parent.width
            height: 3
            anchors.verticalCenter: parent.verticalCenter
            color: Colors.color3
        }
        Rectangle { // vertical line
            width: 3
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            color: Colors.color3
        }
        Rectangle { // center dot
            id: dot
            x: parent.width / 2 - radius
            y: parent.height / 2 - radius
            width: 30
            height: width
            radius: width / 2
            color: Colors.color5
        }
    }
    BalanceFadeArrow {
        source: "../automotive/images/right.svg"
        isPortrait: true
        onClicked: dot.x += parent.step
    }
    BalanceFadeArrow {
        source: "../automotive/images/down.svg"
        Layout.alignment: Qt.AlignHCenter
        isPortrait: false
        Layout.columnSpan: 3
        onClicked: dot.y += parent.step
    }
}
