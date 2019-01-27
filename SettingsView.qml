import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: settingsWindow
    visible: true
    title: "Game settings"
    property int margin: 10
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: margin
        GroupBox {
            id: rowBox
            Layout.fillWidth: true

            RowLayout {
                id: rowLayout
                anchors.fill: parent
                Button {
                    text: "Reset Achievements"
                    Layout.fillWidth: true
                    onClicked: GCtrl.clearAchievements()
                }
            }
        }

        GroupBox {
            id: gridBox
            title: "Select the date you want to play."

            GridLayout {
                id: calendarLayout
                rows: 2
                flow: GridLayout.TopToBottom
                anchors.fill: parent

                Calendar {
                    id: gameDate
                    minimumDate: new Date(2016,0,1)
                    maximumDate: new Date(2017,11,31)
                }
            }
        }

        GroupBox {
            title: "Other Settings"
            Layout.fillWidth: true

            GridLayout {
                id: gridLayout
                rows: 3
                flow: GridLayout.TopToBottom
                anchors.fill: parent
                Layout.fillWidth: true

                Label {
                    text: "Framerate:"
                }
                Label {
                    text: "Difficulty:"
                }
                Label {
                    text: "Starting City:"
                }

                ComboBox {
                    id:frameRate
                    model: ["20","30","40","50","60"]
                    currentIndex: frameRate.find(GameSettings.framerate)
                    Layout.fillWidth: true
                    Component.onCompleted: {
                        // This if-structure had to be implemented to make a conversion between int and string
                        // with the ComboBox and the PlayerStats -class.
                        var framerateString;
                        if (GameSettings.framerate == 20) {
                            framerateString = "20"
                        } else if (GameSettings.framerate == 30) {
                            framerateString = "30"
                        } else if (GameSettings.framerate == 40) {
                            framerateString = "40"
                        } else if (GameSettings.framerate == 50) {
                            framerateString = "50"
                        } else if (GameSettings.framerate == 60) {
                            framerateString = "60"
                        } else {
                            framerateString = "30"
                        }

                        if (find(framerateString) !== -1) {
                            currentIndex = find(framerateString)
                        }
                    }
                }

                ComboBox {
                    id: difficulty
                    model: ["Easy","Normal","Hard","Ultimate"]
                    Layout.fillWidth: true
                    Component.onCompleted: {
                        if (find(GameSettings.difficulty) !== -1) {
                            currentIndex = find(GameSettings.difficulty)
                        }
                    }
                }

                ComboBox {
                    id: startingCity
                    model: ["HKI","JY","OL","TPE"]
                    Layout.fillWidth: true
                    Component.onCompleted: {
                        if (find(GameSettings.startingCity) !== -1) {
                            currentIndex = find(GameSettings.startingCity)
                        }
                    }
                }
            }
        }

        GroupBox {
            id: buttonBox
            Layout.fillWidth: true

            GridLayout {
                id: buttons
                columns: 2
                flow: GridLayout.LeftToRight
                anchors.fill: parent

                Button {
                    text: qsTr("Cancel")
                    Layout.fillWidth: true
                    onClicked: {
                        settingsWindow.close()
                    }
                }

                Button {
                    text: qsTr("Save && Close")
                    Layout.fillWidth: true
                    onClicked: {
                        GameSettings.framerate = frameRate.currentText
                        GameSettings.difficulty = difficulty.currentText
                        GameSettings.gameDate = gameDate.selectedDate
                        GameSettings.startingCity = startingCity.currentText

                        console.debug("Valittu framerate:" + GameSettings.framerate)
                        console.debug("Valittu päivämäärä:" + GameSettings.gameDate)
                        console.debug("Valittu vaikeusaste:" + GameSettings.difficulty)
                        console.debug("Valittu aloituskaupunki:" + GameSettings.startingCity)

                        settingsWindow.close()
                    }
                }
            }
        }
    }
}
