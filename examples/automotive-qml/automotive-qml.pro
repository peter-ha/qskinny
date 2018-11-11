include( $${PWD}/../example.pri )

TARGET = automotive-qml

QT += quickcontrols2

#CONFIG += qtquickcompiler

SOURCES += main.cpp

RESOURCES += resources.qrc

DISTFILES += \
    main.qml \
    Header.qml \
    Content.qml \
    Footer.qml \
    ButtonBar.qml \
    Title.qml \
    MainText.qml \
    SoundControlSlider.qml \
    ToneButton.qml \
    ToneContent.qml \
    BalanceFadeContent.qml \
    BalanceFadeArrowImage.qml \
    Settings.qml \
    imports/Colors.qml \
    imports/qmldir
