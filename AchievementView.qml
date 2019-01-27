import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    anchors.fill: parent
    id: achievementView
    color: "#80C4CCCF"

    Component.onCompleted: {
        // lue achievementit
        if (Achievements.achievementList[0] === false) {
            achievement1.color = "dimgrey"
        }
        if (Achievements.achievementList[1] === false) {
            achievement2.color = "dimgrey"
        }
        if (Achievements.achievementList[2] === false) {
            achievement3.color = "dimgrey"
        }
        if (Achievements.achievementList[3] === false) {
            achievement4.color = "dimgrey"
        }
        if (Achievements.achievementList[4] === false) {
            achievement5.color = "dimgrey"
        }
        if (Achievements.achievementList[5] === false) {
            achievement6.color = "dimgrey"
        }
        if (Achievements.achievementList[6] === false) {
            achievement7.color = "dimgrey"
        }
        if (Achievements.achievementList[7] === false) {
            achievement8.color = "dimgrey"
        }
        if (Achievements.achievementList[8] === false) {
            achievement9.color = "dimgrey"
        }
        if (Achievements.achievementList[9] === false) {
            achievement10.color = "dimgrey"
        }
    }


    GridLayout{
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.fillHeight: true
        rows: 11
        flow: GridLayout.TopToBottom
        anchors.centerIn: parent
        anchors.margins: 20

        Rectangle {
            id: achievement1
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement1Name
                    text: qsTr("Token Collector")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement1Text
                    text: qsTr("Collect 500 tokens in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement2
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement2Name
                    text: qsTr("Token Enthusiast")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement2Text
                    text: qsTr("Collect 1000 tokens in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement3
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement3Name
                    text: qsTr("Token Maniac")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement3Text
                    text: qsTr("Collect 1500 tokens in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement4
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement4Name
                    text: qsTr("Rake")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement4Text
                    text: qsTr("Clean up 5 leafpiles in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement5
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement5Name
                    text: qsTr("Leaf Blower")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement5Text
                    text: qsTr("Clean up 10 leafpiles in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement6
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement6Name
                    text: qsTr("Lawn Sweeper")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement6Text
                    text: qsTr("Clean up 25 leafpiles in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement7
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement7Name
                    text: qsTr("SHOO!")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement7Text
                    text: qsTr("Shoo away 5 moose in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement8
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement8Name
                    text: qsTr("Moose Hunter")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement8Text
                    text: qsTr("Shoo away 10 moose in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement9
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement9Name
                    text: qsTr("Natural Selector")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement9Text
                    text: qsTr("Shoo away 25 moose in one game.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle {
            id: achievement10
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 20
            color: "limegreen"
            border.color: "black"
            GridLayout {
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent

                Text {
                    id: achievement10Name
                    text: qsTr("Not a Filthy Console Peasant")
                    font.bold: true
                    font.pointSize: 24
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: achievement10Text
                    text: qsTr("Start a game with glorious 60 fps setting.")
                    Layout.fillHeight: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Button {
            text: "CLOSE ACHIEVEMENTS"
            Layout.fillWidth: true
            onClicked: {
                showStartView()
            }
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
        }
    }
}
