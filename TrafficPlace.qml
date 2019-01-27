import QtQuick 2.0

Item{
    property QtObject model
    objectName: "trafficPlace"

    Rectangle {
        x: model.location.x - width/2
        y: model.location.y - height/2
        width: 10
        height: 10
        radius: 5
        color: "crimson"

        MouseArea{
            scale: 1.5
            anchors.fill: parent
            onClicked: {
                GCtrl.moveAction(model.stationShortCode)
            }
        }
    }
}

