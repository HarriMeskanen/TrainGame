import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property QtObject model
    objectName: "playerTrain"

    Rectangle{
        property double speed: model.speed
        width: model.width
        height: model.height
        color: model.color

        x: model.location.x - width/2
        y: model.location.y - height/2
        rotation: Math.atan(model.direction.y / model.direction.x) * (180 / Math.PI)


        ProgressBar {
            id: healthBar
            value: PlayerStats.health
            height: parent.height*0.6
            width: parent.width*0.85
            minimumValue: 0
            maximumValue: 100
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            style: ProgressBarStyle {
                background:
                    Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 200
                        implicitHeight: 24
                    }
                progress:
                    Rectangle {
                        color: "mediumturquoise"
                        border.color: "steelblue"
                    }
                }
            }
    }
}


