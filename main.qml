import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: mainWindow
    objectName: "mainWindow"
    visible: true
    title: qsTr("Air Monitor")
    visibility: "FullScreen"

    Grid {
        id: grid
        columns: 2

        anchors.centerIn: parent

        Text { id: lblPM1p0; font.pixelSize: 80; text: qsTr("PM1.0: "); }
        Text { id: txtPM1p0; font.pixelSize: 80; text: qsTr("1.0"); objectName: "txtPM1p0"; }
        Text { id: lblPM2p5; font.pixelSize: 80; text: qsTr("PM2.5: "); }
        Text { id: txtPM2p5; font.pixelSize: 80; text: qsTr("2.5"); objectName: "txtPM2p5"; }
        Text { id: lblPM10;  font.pixelSize: 80; text: qsTr("PM10:  "); }
        Text { id: txtPM1s0; font.pixelSize: 80; text: qsTr("10");  objectName: "txtPM10"; }
    }

    MouseArea {
        anchors.fill: parent
        enabled: false
        cursorShape: Qt.BlankCursor
    }
}
