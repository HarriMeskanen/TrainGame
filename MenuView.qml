import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

Rectangle {
    id: menu
    anchors.fill: parent
    color: "transparent"
    z: 0
    property bool active: false

    function keySPressed() {
        serviceButton.clicked()
    }

    GroupBox {
        id: menuBox
        anchors.left: parent.left
        anchors.top: parent.top
        width: 140
        height: parent.height/4
        x: 100
        y: 100

        GridLayout {
            anchors.fill: parent
            anchors.margins: 5
            rows: 4
            flow: GridLayout.TopToBottom

            Rectangle {
                id: tokenCounter
                color: "limegreen"
                width: 20
                height: 20
                radius: 10

                Text {
                    text: PlayerStats.tokens
                    color: "white"
                    font.bold: true
                    font.pointSize: 20
                    y:parent.height/2-height/2
                    x:parent.width*0.45
                }

                Layout.fillWidth: true
                Layout.fillHeight: true

                Image {
                    source: "qrc:/resources/coin.png"
                    width: 20
                    height: 20
                    y: parent.height/2-height/2
                    x: parent.width*0.1
                }
            }

            Rectangle {
                id: clock
                color: "aliceblue"
                width: 20
                height: 20
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    text: PlayerStats.gameTimeStr
                    color: "black"
                    font.bold: true
                    font.pointSize: 12
                    anchors.centerIn: parent
                }
            }

            Button {
                id: serviceButton
                Layout.fillWidth: true
                Layout.fillHeight: true
                checkable: true
                onClicked: {
                    if(menu.active){
                        if (serviceMenu.state == "closed") {
                            GCtrl.pauseGame()
                            serviceMenu.state = "open"
                            serviceButtonText.text = "CLOSE (S)"
                            serviceMenu.serviceGoFront()
                        } else if (serviceMenu.state == "open") {
                            GCtrl.resumeGame()
                            serviceMenu.state = "closed"
                            serviceButtonText.text = "SERVICE (S)"
                            serviceMenu.serviceGoBack()
                        }
                    }
                }

                Text {
                    id: serviceButtonText
                    text: qsTr("SERVICE (S)")
                    color: "black"
                    font.bold: true
                    font.pointSize: 10
                    y:parent.height/2-height/2
                    x:parent.width*0.35
                }

                Image {
                    source: "qrc:/resources/hammer-28636_1280.png"
                    width: 20
                    height: 20
                    y: parent.height/2-height/2
                    x: parent.width*0.05
                }
            }
            /*
            Button {
                id: achievements
                Layout.fillWidth: true
                Layout.fillHeight: true
                onClicked: {
                    GCtrl.pauseGame()
                    showAchievementView()
                }

                Text {
                    id: achievementButtonText
                    text: qsTr("ACHIEVEMENTS")
                    color: "black"
                    font.bold: true
                    font.pointSize: 10
                    y:parent.height/2-height/2
                    x:parent.width*0.2
                }

                Image {
                    source: "qrc:/resources/medal.png"
                    width: 15
                    height: 20
                    y: parent.height/2-height/2
                    x: parent.width*0.05
                }
            }
            */
            Button {
                id: closeButton
                Layout.fillWidth: true
                Layout.fillHeight: true
                checkable: true
                onClicked: {
                    if(menu.active){
                        menu.active = false
                        GCtrl.resetGame()
                        showStartView()
                    }
                }

                Text {
                    id: quitButtonText
                    text: qsTr("QUIT GAME")
                    color: "black"
                    font.bold: true
                    font.pointSize: 10
                    y:parent.height/2-height/2
                    x:parent.width*0.35
                }

                Image {
                    source: "qrc:/resources/quit.png"
                    width: 20
                    height: 20
                    y: parent.height/2-height/2
                    x: parent.width*0.05
                }
            }
        }

    }

    ServiceView {
        id: serviceMenu
        state: "closed"
        x: parent.width
        z: 50
    }
}

