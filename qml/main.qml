import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    property var resolutions: [
        {"height": 480, "width": 320}, // HVGA
        {"height": 640, "width": 480}, // VGA
        {"height": 800, "width": 480}, // WVGA
        {"height": 800, "width": 600}, // SVGA
        {"height": 640, "width": 360}, // nHD
        {"height": 960, "width": 540},  // qHD
	{"height": 1280, "width": 720},  // 720p
	{"height": 1920, "width": 1080}  // 1080p
    ]

    property int currentResolution: 3
    property bool isScreenPortrait: height >= width

    visible: true
    width: resolutions[currentResolution]["width"]
    height: resolutions[currentResolution]["height"]
    title: "%ProjectName%"

    StackView {
        id: stackview
        anchors.fill: parent
        focus: true

        Keys.onReleased: {
            if (event.key === Qt.Key_Back) {
                if (stackview.depth > 1)
                    stackview.pop()

                event.accepted = true
            }
        }
    }

    Button {
        anchors.centerIn: parent
        text: qsTr("Click me!")
        onClicked: ui.showMessage("Thanks!")
    }
}

