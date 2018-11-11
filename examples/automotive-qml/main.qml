import QtQuick 2.11

Item {
    id: root
    width: 1024
    height: 576
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "../automotive/images/background.jpg"
    }
    Header {
        id: header
        width: root.width
        anchors.top: parent.top
        anchors.left: parent.left
    }
    Content {
        id: content
        width: root.width
        anchors.top: header.bottom
        anchors.bottom: footer.top
    }
    Footer {
        id: footer
        height: 56
        width: root.width
        anchors.bottom: parent.bottom
    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}
