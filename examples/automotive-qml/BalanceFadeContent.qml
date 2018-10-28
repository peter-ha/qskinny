import QtQuick 2.11
import QtQuick.Layouts 1.11
import "imports"

GridLayout {
//    rows: 3
    columns: 3
    rowSpacing: 5
    columnSpacing: 5

    BalanceFadeArrow { // ### implement button clicks
        source: "/../automotive/images/up.svg"
        Layout.alignment: Qt.AlignHCenter
        isPortrait: false
        Layout.columnSpan: 3
    }
    BalanceFadeArrow {
        source: "/../automotive/images/left.svg"
        isPortrait: true
    }
    Image {
        id: car
        source: "/../automotive/images/car.svg"
        width: 500 // ###
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
            anchors.centerIn: parent
            width: 30
            height: width
            radius: width / 2
            color: Colors.color5
        }
    }
    BalanceFadeArrow {
        source: "/../automotive/images/right.svg"
        isPortrait: true
    }
    BalanceFadeArrow {
        source: "/../automotive/images/down.svg"
        Layout.alignment: Qt.AlignHCenter
        isPortrait: false
        Layout.columnSpan: 3
    }
}
