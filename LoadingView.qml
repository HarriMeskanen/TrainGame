import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


Rectangle {
    anchors.fill: parent
    color: "#80C4CCCF"
    focus: true
    z:10

    Rectangle {

        anchors.centerIn: parent
        color: "limegreen"
        width: 320
        height: 320
        radius: 160

        GridLayout {
            anchors.centerIn: parent
            rows: 2
            flow: GridLayout.TopToBottom
            anchors.margins: 20
            width: 400
            height: 150

            Timer {
                interval: 1500
                running: true
                repeat: false
                onTriggered: infoText.text = "WARMING UP ENGINES..."
            }

            Timer {
                interval: 3000
                running: true
                repeat: false
                onTriggered: infoText.text = "SHOVELING SNOW..."
            }

            Timer {
                interval: 6000
                running: true
                repeat: false
                onTriggered: infoText.text = "FETCHING TIMETABLES..."
            }

            Text {
                id: infoText
                color: "white"
                text: qsTr("LOADING TRAINS...")
                font.pointSize: 22
                font.bold: true
                Layout.fillHeight: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            BusyIndicator {
                id: loadingIcon
                width: 150
                height: 150
                anchors.centerIn: parent
            }
        }
    }
}

