import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: menu
    width: parent.width*0.75
    height: parent.height/4
    y: 0
    color: "#80C4CCCF"

    function serviceGoFront() {
        goFront.start()
    }

    function serviceGoBack() {
        goBack.start()
    }

    NumberAnimation {
        id: goFront
        target: menu
        property: "x"
        from: parent.width
        to: parent.width-width
        duration: 300
    }

    NumberAnimation {
        id: goBack
        target: menu
        property: "x"
        from: parent.width-width
        to: parent.width
        duration: 300
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 2

        GroupBox {
            id: repairTrain
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                anchors.fill: parent
                rows: 3
                flow: GridLayout.TopToBottom

                Rectangle {
                    height: 20
                    color: "limegreen"
                    radius: 10

                    Text {
                        id:repairPrice
                        text: 2*(100-PlayerStats.health)
                        color: "white"
                        font.bold: true
                        font.pointSize: 12
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

                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "Repair Train"
                    style: ButtonStyle {
                        background: Rectangle {
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "steelblue" : "skyblue" }
                                GradientStop { position: 1 ; color: control.pressed ? "skyblue" : "steelblue" }
                            }
                        }
                    }
                    onClicked: {
                        GCtrl.repairPlayerTrain()
                    }
                }

                Rectangle {
                    height: 40
                    color: "antiquewhite"
                    radius: 10
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    GridLayout {
                        rows: 3
                        columns: 2
                        flow: GridLayout.LeftToRight
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 10

                        Image {
                            id: healthIcon
                            source: "qrc:/resources/health.png"
                            Layout.preferredWidth: 20
                            Layout.preferredHeight: 20
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        Text {
                            id: healthText
                            property string health: PlayerStats.health
                            text: health + "/100"
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        Image {
                            id: speedIcon
                            source: "qrc:/resources/speed.png"
                            Layout.preferredWidth: 20
                            Layout.preferredHeight: 20
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        Text {
                            id: speedText
                            text: PlayerStats.speed
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        Image {
                            id: jumpIcon
                            source: "qrc:/resources/jump.png"
                            Layout.preferredWidth: 20
                            Layout.preferredHeight: 20
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        Text {
                            id: jumpCheckMark
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: "NO"
                        }
                    }
                }
            }
        }

        GroupBox {
            id: trainUpgrades
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                anchors.fill: parent
                flow: GridLayout.LeftToRight
                columns: 2
                rows: 2

                Rectangle {
                    width: 50
                    color: "limegreen"
                    radius: 10

                    Text {
                        id: speedPrice
                        text: "100"
                        color: "white"
                        font.bold: true
                        font.pointSize: 12
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

                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "Upgrade Speed"
                    checkable: true
                    style: ButtonStyle {
                        background: Rectangle {
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "steelblue" : "skyblue" }
                                GradientStop { position: 1 ; color: control.pressed ? "skyblue" : "steelblue" }
                            }
                        }
                    }
                    onClicked: {
                        GCtrl.upgradeSpeed()
                    }
                }

                Rectangle {
                    width: 10
                    color: "limegreen"
                    radius: 10

                    Text {
                        id: jumpPrice
                        text: "250"
                        color: "white"
                        font.bold: true
                        font.pointSize: 12
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

                Button {
                    id: buyJumpButton
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "Buy Jump"
                    enabled: !PlayerStats.jump
                    style: ButtonStyle {
                        background: Rectangle {
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "steelblue" : "skyblue" }
                                GradientStop { position: 1 ; color: control.pressed ? "skyblue" : "steelblue" }
                            }
                        }
                    }
                    onClicked: {
                        GCtrl.upgradeJump()
                        if (PlayerStats.jump) {
                            jumpCheckMark.text = "YES"
                            buyJumpButton.text = "Press space for jump!"
                        } else {
                            jumpCheckMark.text = "NO"
                        }
                    }
                }
                // RIFLES TO BE ADDED IN FUTURE GAME VERSIONS
                /*
                Rectangle {
                    width: 10
                    color: "limegreen"
                    radius: 10

                    Text {
                        id: riflePrice
                        text: "Price3"
                        color: "white"
                        font.bold: true
                        font.pointSize: 12
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

                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "Buy Rifle"
                    style: ButtonStyle {
                        background: Rectangle {
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "steelblue" : "skyblue" }
                                GradientStop { position: 1 ; color: control.pressed ? "skyblue" : "steelblue" }
                            }
                        }
                    }
                } */
            }
        }
    }
}
