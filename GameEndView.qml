import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

Rectangle {
    width: 300
    height: 100
    color: "white"
    border.color: "black"
    anchors.centerIn: parent

    GridLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 20
        rows: 2
        flow: GridLayout.TopToBottom

        Text {
            font.bold: true
            font.pointSize: 24
            text: "GAME OVER!"
        }

        GridLayout {
            columns: 3
            flow: GridLayout.LeftToRight

            Text {
                font.bold: true
                font.pointSize: 16
                text: "Score: "
            }

            Image {
                id: tokenIcon
                source: "qrc:/resources/coin.png"
                height: 20
                width: 20
            }

            Text {
                font.bold: true
                font.pointSize: 16
                text: PlayerStats.totalTokens
            }
        }
    }
}
