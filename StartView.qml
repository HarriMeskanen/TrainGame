import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4


Item {
    anchors.fill: parent

    /*Connections{
        target: GCtrl
        onGameStarted:{
            if(status){
                showGameMapView()
            }
            else{
                textLabel.text = "Game initialization failed"
            }
        }
    }*/

    GroupBox {
        anchors.fill: parent
        anchors.margins: 50

        GridLayout{
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
            rows:4
            flow: GridLayout.TopToBottom

            Button{
                id: playButton
                text: qsTr("PLAY")
                checkable: true
                Layout.fillWidth: true
                Layout.fillHeight: true
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
                  showGameMapView()
                }
            }

            Button{
                id: settingsButton
                text: qsTr("SETTINGS")
                Layout.fillWidth: true
                Layout.fillHeight: true
                style: ButtonStyle {
                    background: Rectangle {
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "peachpuff" : "papayawhip" }
                            GradientStop { position: 1 ; color: control.pressed ? "papayawhip" : "peachpuff" }
                        }
                    }
                }
                onClicked: {
                    showSettingsView()
                }
            }

            Button{
                id: achievementButton
                text: qsTr("ACHIEVEMENTS")
                checkable: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                style: ButtonStyle {
                    background: Rectangle {
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "teal" : "turquoise" }
                            GradientStop { position: 1 ; color: control.pressed ? "turquoise" : "teal" }
                        }
                    }
                }
                onClicked: {
                    showAchievementView()
                }
            }

            Button{
                id: quitButton
                text: qsTr("QUIT")
                Layout.fillWidth: true
                Layout.fillHeight: true
                style: ButtonStyle {
                    background: Rectangle {
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "lightsteelblue" : "lightskyblue" }
                            GradientStop { position: 1 ; color: control.pressed ? "lightskyblue" : "lightsteelblue" }
                        }
                    }
                }
                onClicked: {
                    GCtrl.closeApplication()
                    Qt.quit()
                }
            }
        }
    }
}
